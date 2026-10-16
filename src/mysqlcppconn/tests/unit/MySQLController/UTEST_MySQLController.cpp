#include <cppconn/exception.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/mysqlcppconn/tests/mocks/MySQLControllerSpy.h"

using namespace app;
using namespace mysqli;
using namespace testing;

class UTEST_MySQLController : public Test
{
 public:
  UTEST_MySQLController()
  {
    ctx->set_mysql_host("db.example.org");
    ctx->set_mysql_port("13306");
    ctx->set_mysql_user("random_user");
    ctx->set_mysql_password("random password");
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};

  std::shared_ptr<MySQLControllerSpy> controller{
      std::make_shared<NiceMock<MySQLControllerSpy>>()};
};

TEST_F(UTEST_MySQLController, no_context)
{
  EXPECT_FALSE(controller->connect({}));
}

TEST_F(UTEST_MySQLController, connects_with_the_context_credentials)
{
  EXPECT_CALL(*controller, open_connection("tcp://db.example.org:13306",
                                           "random_user", "random password"))
      .Times(1)
      .WillOnce(Return(ByMove(nullptr)));

  EXPECT_FALSE(controller->connect(ctx));
  EXPECT_FALSE(controller->connected());
}

TEST_F(UTEST_MySQLController, driver_exception_is_a_connect_failure)
{
  EXPECT_CALL(*controller, open_connection(_, _, _))
      .Times(1)
      .WillOnce(Throw(sql::SQLException("random failure")));

  EXPECT_FALSE(controller->connect(ctx));
  EXPECT_FALSE(controller->connected());
}

TEST_F(UTEST_MySQLController, no_date_before_connect)
{
  EXPECT_CALL(*controller, execute_query(_)).Times(0);

  EXPECT_TRUE(controller->get_current_date().empty());
}

TEST_F(UTEST_MySQLController, failed_query_gives_empty_date)
{
  controller->connect(ctx);

  EXPECT_CALL(*controller, execute_query("SELECT CURDATE();"))
      .Times(1)
      .WillOnce(Return(ByMove(nullptr)));

  EXPECT_TRUE(controller->get_current_date().empty());
}

TEST_F(UTEST_MySQLController, query_exception_gives_empty_date)
{
  controller->connect(ctx);

  EXPECT_CALL(*controller, execute_query(_))
      .Times(1)
      .WillOnce(Throw(sql::SQLException("random failure")));

  EXPECT_TRUE(controller->get_current_date().empty());
}

TEST_F(UTEST_MySQLController, context_and_connection_are_released)
{
  ctx->set_mysqlconn(controller);
  controller->connect(ctx);

  std::weak_ptr<ApplicationContext> wctx = ctx;
  std::weak_ptr<MySQLControllerSpy> wcontroller = controller;

  ctx.reset();
  controller.reset();

  EXPECT_TRUE(wctx.expired());
  EXPECT_TRUE(wcontroller.expired());
}
