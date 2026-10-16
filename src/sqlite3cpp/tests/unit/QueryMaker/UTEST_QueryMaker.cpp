#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

using namespace sqlite3i::sqlmaker;
using namespace testing;

class UTEST_QueryMaker : public Test
{
 public:
  std::shared_ptr<QueryMaker> qmaker{std::make_shared<QueryMaker>()};
};

TEST_F(UTEST_QueryMaker, date_query_selects_the_current_date)
{
  EXPECT_EQ(qmaker->make_date_query(), "SELECT date('now');");
}
