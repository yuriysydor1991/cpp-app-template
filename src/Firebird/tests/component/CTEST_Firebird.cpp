#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/Firebird/Firebird.h"
#include "src/Firebird/IFbClient.h"
#include "src/Firebird/driver/FbClient.h"
#include "src/Firebird/tests/mocks/FakeFbClient.h"
#include "src/Firebird/tests/mocks/InjectedFirebird.h"
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

class CTEST_Firebird : public Test
{
 public:
  CTEST_Firebird()
      : fake{std::make_shared<FakeFbClient>()},
        fb{std::make_shared<InjectedFirebird>(fake)},
        ctx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    ctx->set_fb_host("localhost");
    ctx->set_fb_port("3050");
    ctx->set_fb_dbname("employee");
    ctx->set_fb_user("SYSDBA");
    ctx->set_fb_password("masterkey");
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<FakeFbClient> fake;
  std::shared_ptr<InjectedFirebird> fb;
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
