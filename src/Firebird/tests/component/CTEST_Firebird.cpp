#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/Firebird/Firebird.h"
#include "src/Firebird/IFbClient.h"
#include "src/Firebird/driver/FbClient.h"
#include "src/app/ApplicationContext.h"

using namespace firebirdi;
using namespace app;
using namespace testing;

// Link-time seam: the component is assembled with a fake driver, so the real
// fbclient backed factory is never linked into this test.
namespace firebirdi::driver
{
std::shared_ptr<IFbClient> create_fb_client() { return nullptr; }
}  // namespace firebirdi::driver

namespace
{

/// @brief Records what the Firebird orchestration hands to the native driver
/// and returns canned responses, so the whole component pipeline (connection
/// string maker + query maker + orchestration) can be verified end to end
/// without a running Firebird server.
class FakeFbClient : public IFbClient
{
 public:
  bool attach(const std::string& database, const std::string& user,
              const std::string& password) override
  {
    last_database = database;
    last_user = user;
    last_password = password;
    is_attached = attach_result;
    return attach_result;
  }

  void detach() override { is_attached = false; }
  bool attached() const override { return is_attached; }

  std::string query_scalar(const std::string& query) override
  {
    last_query = query;
    return scalar_result;
  }

  bool attach_result{true};
  std::string scalar_result;
  bool is_attached{false};

  std::string last_database;
  std::string last_user;
  std::string last_password;
  std::string last_query;
};

/// @brief Wires the fake driver into the real Firebird component.
class ComponentFirebird : public Firebird
{
 public:
  explicit ComponentFirebird(std::shared_ptr<IFbClient> nclient)
      : injected{nclient}
  {
  }

 protected:
  std::shared_ptr<IFbClient> create_client() override { return injected; }

 private:
  std::shared_ptr<IFbClient> injected;
};

}  // namespace

class CTEST_Firebird : public Test
{
 public:
  CTEST_Firebird()
      : fake{std::make_shared<FakeFbClient>()},
        fb{std::make_shared<ComponentFirebird>(fake)},
        ctx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    ctx->fb_host = "localhost";
    ctx->fb_port = "3050";
    ctx->fb_dbname = "employee";
    ctx->fb_user = "SYSDBA";
    ctx->fb_password = "masterkey";
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<FakeFbClient> fake;
  std::shared_ptr<ComponentFirebird> fb;
  std::shared_ptr<ApplicationContext> ctx;
};

TEST_F(CTEST_Firebird, connect_builds_conn_string_and_passes_credentials)
{
  ASSERT_TRUE(fb->connect(ctx));

  EXPECT_TRUE(fb->connected());
  EXPECT_EQ(fake->last_database, "localhost/3050:employee");
  EXPECT_EQ(fake->last_user, "SYSDBA");
  EXPECT_EQ(fake->last_password, "masterkey");
}

TEST_F(CTEST_Firebird, get_current_date_runs_the_firebird_date_query)
{
  fake->scalar_result = "2026-05-20";

  ASSERT_TRUE(fb->connect(ctx));

  EXPECT_EQ(fb->get_current_date(), "2026-05-20");
  EXPECT_THAT(fake->last_query, HasSubstr("CURRENT_DATE"));
  EXPECT_THAT(fake->last_query, HasSubstr("RDB$DATABASE"));
}

TEST_F(CTEST_Firebird, failed_attachment_yields_no_date)
{
  fake->attach_result = false;

  EXPECT_FALSE(fb->connect(ctx));
  EXPECT_FALSE(fb->connected());
  EXPECT_TRUE(fb->get_current_date().empty());
}
