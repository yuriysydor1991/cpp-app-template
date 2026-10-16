#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/PgSQLxx/PgSQL.h"
#include "src/app/ApplicationContext.h"

using namespace pgsqli;
using namespace app;
using namespace testing;

/**
 * @brief Talks to a real PostgreSQL server reached with the context defaults
 * or the PGHOST/PGPORT/PGDATABASE/PGUSER/PGPASSWORD environment variables.
 * The cases needing a server get skipped when none is reachable.
 */
class CTEST_PgSQL : public Test
{
 public:
  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
  std::shared_ptr<PgSQL> pgsql{std::make_shared<PgSQL>()};
};

TEST_F(CTEST_PgSQL, unreachable_server_fails_cleanly)
{
  ctx->set_pg_host("127.0.0.1");
  ctx->set_pg_port("1");

  EXPECT_FALSE(pgsql->connect(ctx));
  EXPECT_FALSE(pgsql->connected());
  EXPECT_TRUE(pgsql->get_current_date().empty());
}

TEST_F(CTEST_PgSQL, fetches_the_current_date)
{
  if (!pgsql->connect(ctx)) {
    GTEST_SKIP() << "No PostgreSQL server reachable at '" << ctx->get_pg_host()
                 << "' as '" << ctx->get_pg_user() << "'";
  }

  EXPECT_TRUE(pgsql->connected());
  EXPECT_THAT(pgsql->get_current_date(),
              MatchesRegex("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
}
