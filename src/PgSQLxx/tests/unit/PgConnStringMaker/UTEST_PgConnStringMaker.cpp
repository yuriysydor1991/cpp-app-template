#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>

#include "src/PgSQLxx/helpers/PgConnStringMaker.h"
#include "src/app/ApplicationContext.h"

using namespace pgsqli::helpers;
using namespace app;
using namespace testing;

class UTEST_PgConnStringMaker : public Test
{
 public:
  UTEST_PgConnStringMaker()
  {
    ctx->set_pg_dbname("postgres");
    ctx->set_pg_user("user");
    ctx->set_pg_password("secret");
    ctx->set_pg_host("localhost");
    ctx->set_pg_port({});
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<PgConnStringMaker> maker{
      std::make_shared<PgConnStringMaker>()};
  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(UTEST_PgConnStringMaker, null_context_returns_empty)
{
  EXPECT_TRUE(maker->make_conn_string(nullptr).empty());
}

TEST_F(UTEST_PgConnStringMaker, every_value_is_quoted)
{
  ctx->set_pg_port("5433");

  EXPECT_EQ(maker->make_conn_string(ctx),
            "dbname='postgres' user='user' password='secret' "
            "host='localhost' port='5433'");
}

TEST_F(UTEST_PgConnStringMaker, empty_values_are_skipped)
{
  ctx->set_pg_password({});
  ctx->set_pg_host({});

  EXPECT_EQ(maker->make_conn_string(ctx), "dbname='postgres' user='user'");
}

TEST_F(UTEST_PgConnStringMaker, quotes_and_backslashes_are_escaped)
{
  ctx->set_pg_password(R"(my 'pass\word)");

  EXPECT_THAT(maker->make_conn_string(ctx),
              HasSubstr(R"(password='my \'pass\\word')"));
}

TEST_F(UTEST_PgConnStringMaker, values_can_not_inject_keywords)
{
  ctx->set_pg_dbname("x host=evil");
  ctx->set_pg_host({});

  EXPECT_EQ(maker->make_conn_string(ctx),
            "dbname='x host=evil' user='user' password='secret'");
}

TEST_F(UTEST_PgConnStringMaker, libpq_environment_overrides_defaults)
{
  ASSERT_EQ(setenv("PGUSER", "env_user", 1), 0);
  ASSERT_EQ(setenv("PGPASSWORD", "env pass", 1), 0);

  const auto envCtx = std::make_shared<ApplicationContext>(argc, argv);

  unsetenv("PGUSER");
  unsetenv("PGPASSWORD");

  EXPECT_THAT(maker->make_conn_string(envCtx),
              HasSubstr("user='env_user' password='env pass'"));
}

TEST_F(UTEST_PgConnStringMaker, defaults_without_environment)
{
  unsetenv("PGDATABASE");
  unsetenv("PGUSER");
  unsetenv("PGPASSWORD");
  unsetenv("PGHOST");
  unsetenv("PGPORT");

  const auto defCtx = std::make_shared<ApplicationContext>(argc, argv);

  EXPECT_EQ(maker->make_conn_string(defCtx),
            "dbname='" + ApplicationContext::default_pg_name + "' user='" +
                ApplicationContext::default_pg_user + "' password='" +
                ApplicationContext::default_pg_password + "' host='" +
                ApplicationContext::default_pg_host + "'");
}
