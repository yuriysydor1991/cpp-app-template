#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "PgSQLSpy.h"
#include "src/app/ApplicationContext.h"

using namespace pgsqli;
using namespace app;
using namespace testing;

class UTEST_PgSQL : public Test
{
 public:
  UTEST_PgSQL()
  {
    ctx->set_pg_dbname("db");
    ctx->set_pg_user("user");
    ctx->set_pg_password("p'w");
    ctx->set_pg_host({});
    ctx->set_pg_port({});
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
  std::shared_ptr<PgSQLSpy> pgsql{std::make_shared<PgSQLSpy>()};
};

TEST_F(UTEST_PgSQL, null_context_fails)
{
  EXPECT_FALSE(pgsql->connect(nullptr));
  EXPECT_EQ(pgsql->connectionsCreated, 0);
}

TEST_F(UTEST_PgSQL, connects_with_the_context_credentials)
{
  EXPECT_FALSE(pgsql->connect(ctx));
  EXPECT_EQ(pgsql->connectionsCreated, 1);
  EXPECT_EQ(pgsql->connStr, R"(dbname='db' user='user' password='p\'w')");
}

TEST_F(UTEST_PgSQL, no_date_without_connection)
{
  EXPECT_FALSE(pgsql->connected());
  EXPECT_TRUE(pgsql->get_current_date().empty());

  EXPECT_FALSE(pgsql->connect(ctx));
  EXPECT_FALSE(pgsql->connected());
  EXPECT_TRUE(pgsql->get_current_date().empty());
}

TEST_F(UTEST_PgSQL, context_owning_the_connection_gets_released)
{
  const std::weak_ptr<ApplicationContext> weakCtx{ctx};
  const std::weak_ptr<PgSQLSpy> weakConn{pgsql};

  ctx->set_pg_connection(pgsql);
  pgsql->connect(ctx);

  pgsql.reset();
  ctx.reset();

  EXPECT_TRUE(weakCtx.expired());
  EXPECT_TRUE(weakConn.expired());
}
