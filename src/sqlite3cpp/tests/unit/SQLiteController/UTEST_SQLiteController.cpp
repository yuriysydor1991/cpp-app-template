#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/sqlite3cpp/SQLiteController.h"
#include "src/sqlite3cpp/tests/mocks/QueryMakerMock.h"
#include "src/sqlite3cpp/tests/mocks/SQLiteControllerMock.h"

using namespace app;
using namespace sqlite3i;
using namespace sqlite3i::sqlmaker;
using namespace testing;

class UTEST_SQLiteController : public Test
{
 public:
  UTEST_SQLiteController() { actx->set_db_dbname(":memory:"); }

  /// @brief Connects a controller fed with the given query instead of the
  /// date one and returns what its get_current_date yields.
  std::string date_for_query(const std::string& query)
  {
    auto qmock = std::make_shared<QueryMakerMock>();
    auto cmock = std::make_shared<SQLiteControllerMock>();

    EXPECT_CALL(*cmock, create_query_maker).WillOnce(Return(qmock));
    EXPECT_CALL(*qmock, make_date_query).WillOnce(ReturnRefOfCopy(query));

    EXPECT_TRUE(cmock->connect(actx));

    return cmock->get_current_date();
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> actx{
      std::make_shared<ApplicationContext>(argc, argv)};
  std::shared_ptr<SQLiteController> controller{
      std::make_shared<SQLiteController>()};
};

TEST_F(UTEST_SQLiteController, no_context_fails_to_connect)
{
  EXPECT_FALSE(controller->connect(nullptr));
  EXPECT_FALSE(controller->connected());
}

TEST_F(UTEST_SQLiteController, not_connected_yields_empty_date)
{
  EXPECT_FALSE(controller->connected());
  EXPECT_TRUE(controller->get_current_date().empty());
}

TEST_F(UTEST_SQLiteController, in_memory_database_connects)
{
  EXPECT_TRUE(controller->connect(actx));
  EXPECT_TRUE(controller->connected());
}

TEST_F(UTEST_SQLiteController, current_date_is_an_iso_date)
{
  ASSERT_TRUE(controller->connect(actx));

  EXPECT_THAT(controller->get_current_date(),
              MatchesRegex("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
}

TEST_F(UTEST_SQLiteController, failing_query_step_yields_empty_date)
{
  // prepares fine, but the integer overflow error raises on the step
  EXPECT_TRUE(date_for_query("SELECT abs(-9223372036854775808);").empty());
}

TEST_F(UTEST_SQLiteController, invalid_query_yields_empty_date)
{
  EXPECT_TRUE(date_for_query("SELECT value FROM no_such_table;").empty());
}

TEST_F(UTEST_SQLiteController, empty_result_yields_empty_date)
{
  EXPECT_TRUE(date_for_query("SELECT 1 WHERE 0;").empty());
}

TEST_F(UTEST_SQLiteController, uncreatable_directory_fails_to_connect)
{
  actx->set_db_dbname("/dev/null/test.db");

  EXPECT_FALSE(controller->connect(actx));
  EXPECT_FALSE(controller->connected());
}

TEST_F(UTEST_SQLiteController, context_and_controller_are_released)
{
  std::weak_ptr<ApplicationContext> wctx{actx};
  std::weak_ptr<SQLiteController> wcontroller{controller};

  actx->set_dbconn(controller);

  ASSERT_TRUE(controller->connect(actx));

  controller.reset();
  actx.reset();

  EXPECT_TRUE(wctx.expired());
  EXPECT_TRUE(wcontroller.expired());
}
