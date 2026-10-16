#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/mongodbcxx/helpers/MongoDBConnStringMaker.h"
#include "src/mongodbcxx/mongocxx-includes.h"

using namespace mongodbcxxi::helpers;
using namespace app;
using namespace testing;

class UTEST_MongoDBConnStringMaker : public Test
{
 public:
  UTEST_MongoDBConnStringMaker()
  {
    for (const char* name : envNames) {
      unsetenv(name);
    }

    ctx = std::make_shared<ApplicationContext>(argc, argv);
  }

  ~UTEST_MongoDBConnStringMaker() override
  {
    for (const char* name : envNames) {
      unsetenv(name);
    }
  }

  void fill_credentials()
  {
    ctx->set_db_username("user");
    ctx->set_db_password("pass");
    ctx->set_db_host("db.example.org");
    ctx->set_db_port("27018");
    ctx->set_db_name("templatedb");
  }

  inline static constexpr const char* const envNames[] = {
      "MONGODB_HOST",     "MONGODB_PORT", "MONGODB_DATABASE",  "MONGODB_USER",
      "MONGODB_PASSWORD", "MONGODB_TLS",  "MONGODB_TIMEOUT_MS"};

  inline static const std::string timeouts{
      "serverSelectionTimeoutMS=5000&connectTimeoutMS=5000"};

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx;
};

TEST_F(UTEST_MongoDBConnStringMaker, null_context_returns_empty)
{
  EXPECT_TRUE(MongoDBConnStringMaker::make_conn_string(nullptr).empty());
}

TEST_F(UTEST_MongoDBConnStringMaker, defaults_to_the_local_server)
{
  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://localhost:27017/?" + timeouts);
}

TEST_F(UTEST_MongoDBConnStringMaker, empty_timeout_leaves_the_driver_defaults)
{
  ctx->set_db_timeout_ms({});

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://localhost:27017/");
}

TEST_F(UTEST_MongoDBConnStringMaker, credentials_turn_the_tls_on)
{
  fill_credentials();

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://user:pass@db.example.org:27018/templatedb?" + timeouts +
                "&tls=true");
}

TEST_F(UTEST_MongoDBConnStringMaker, tls_value_overrides_the_default)
{
  fill_credentials();
  ctx->set_db_tls("false");

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://user:pass@db.example.org:27018/templatedb?" + timeouts +
                "&tls=false");

  ctx->set_db_username({});
  ctx->set_db_tls("true");

  EXPECT_EQ(
      MongoDBConnStringMaker::make_conn_string(ctx),
      "mongodb://db.example.org:27018/templatedb?" + timeouts + "&tls=true");
}

TEST_F(UTEST_MongoDBConnStringMaker, password_without_username_is_skipped)
{
  ctx->set_db_password("pass");

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://localhost:27017/?" + timeouts);
}

TEST_F(UTEST_MongoDBConnStringMaker, username_without_password)
{
  ctx->set_db_username("user");

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(ctx),
            "mongodb://user@localhost:27017/?" + timeouts + "&tls=true");
}

TEST_F(UTEST_MongoDBConnStringMaker, special_characters_are_percent_encoded)
{
  static const mongocxx::instance driver{};

  fill_credentials();
  ctx->set_db_username("us@er:x");
  ctx->set_db_password("p@ss:w/o%rd?#&=");
  ctx->set_db_name("my+db");

  const std::string connString = MongoDBConnStringMaker::make_conn_string(ctx);

  EXPECT_THAT(connString,
              StartsWith("mongodb://us%40er%3Ax:p%40ss%3Aw%2Fo%25rd%3F%23%26%"
                         "3D@db.example.org:27018/my%2Bdb?"));

  const mongocxx::uri uri{connString};

  ASSERT_EQ(uri.hosts().size(), 1U);
  EXPECT_EQ(uri.hosts().front().name, "db.example.org");
  EXPECT_EQ(uri.hosts().front().port, 27018);
  EXPECT_EQ(uri.username(), "us@er:x");
  EXPECT_EQ(uri.password(), "p@ss:w/o%rd?#&=");
  EXPECT_EQ(uri.database(), "my+db");
  EXPECT_TRUE(uri.tls());
  EXPECT_EQ(uri.server_selection_timeout_ms(), 5000);
  EXPECT_EQ(uri.connect_timeout_ms(), 5000);
}

TEST_F(UTEST_MongoDBConnStringMaker, environment_overrides_the_defaults)
{
  setenv("MONGODB_HOST", "env.example.org", 1);
  setenv("MONGODB_PORT", "27019", 1);
  setenv("MONGODB_DATABASE", "envdb", 1);
  setenv("MONGODB_USER", "envuser", 1);
  setenv("MONGODB_PASSWORD", "envpass", 1);
  setenv("MONGODB_TLS", "false", 1);
  setenv("MONGODB_TIMEOUT_MS", "1500", 1);

  const auto envCtx = std::make_shared<ApplicationContext>(argc, argv);

  EXPECT_EQ(MongoDBConnStringMaker::make_conn_string(envCtx),
            "mongodb://envuser:envpass@env.example.org:27019/envdb?"
            "serverSelectionTimeoutMS=1500&connectTimeoutMS=1500&tls=false");
}
