#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/mysqlcppconn/MySQLController.h"

using namespace app;
using namespace mysqli;
using namespace testing;

/**
 * @brief Talks to the MySQL server given by the MYSQL_* environment variables
 * or the ApplicationContext defaults. The cases needing the server are skipped
 * when none is reachable.
 */
class CTEST_MySQLController : public Test
{
 public:
  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};

  std::shared_ptr<MySQLController> controller{
      std::make_shared<MySQLController>()};

  std::string unreachable() const
  {
    return "No MySQL server reachable at " + ctx->get_mysql_host() + ":" +
           ctx->get_mysql_port() + " as the " + ctx->get_mysql_user() + " user";
  }
};

TEST_F(CTEST_MySQLController, unreachable_server_is_a_connect_failure)
{
  ctx->set_mysql_host("127.0.0.1");
  ctx->set_mysql_port("1");

  EXPECT_FALSE(controller->connect(ctx));
  EXPECT_FALSE(controller->connected());
}

TEST_F(CTEST_MySQLController, current_date_from_the_server)
{
  if (!controller->connect(ctx)) {
    GTEST_SKIP() << unreachable();
  }

  EXPECT_TRUE(controller->connected());
  EXPECT_THAT(controller->get_current_date(),
              MatchesRegex("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
}
