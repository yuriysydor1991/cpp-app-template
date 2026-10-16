#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/PgSQLxx/sql/QueryMaker.h"

using namespace pgsqli::sql;
using namespace testing;

class UTEST_QueryMaker : public Test
{
 public:
  std::shared_ptr<QueryMaker> qmaker{std::make_shared<QueryMaker>()};
};

TEST_F(UTEST_QueryMaker, date_query)
{
  EXPECT_EQ(qmaker->make_date_query(), "SELECT CURRENT_DATE;");
}
