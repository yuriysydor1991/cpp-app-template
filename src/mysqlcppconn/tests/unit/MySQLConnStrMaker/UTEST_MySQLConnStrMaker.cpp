#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/mysqlcppconn/helpers/MySQLConnStrMaker.h"

using namespace app;
using namespace mysqli::helpers;
using namespace testing;

class UTEST_MySQLConnStrMaker : public Test
{
 public:
  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};

  MySQLConnStrMaker maker;
};

TEST_F(UTEST_MySQLConnStrMaker, no_context)
{
  EXPECT_TRUE(maker.make_conn_string({}).empty());
}

TEST_F(UTEST_MySQLConnStrMaker, tcp_scheme_for_a_plain_host)
{
  ctx->set_mysql_host("db.example.org");
  ctx->set_mysql_port("13306");

  EXPECT_EQ(maker.make_conn_string(ctx), "tcp://db.example.org:13306");
}

TEST_F(UTEST_MySQLConnStrMaker, no_port)
{
  ctx->set_mysql_host("127.0.0.1");
  ctx->set_mysql_port("");

  EXPECT_EQ(maker.make_conn_string(ctx), "tcp://127.0.0.1");
}

TEST_F(UTEST_MySQLConnStrMaker, url_host_keeps_its_scheme)
{
  ctx->set_mysql_host("unix:///run/mysqld/mysqld.sock");
  ctx->set_mysql_port("");

  EXPECT_EQ(maker.make_conn_string(ctx), "unix:///run/mysqld/mysqld.sock");
}
