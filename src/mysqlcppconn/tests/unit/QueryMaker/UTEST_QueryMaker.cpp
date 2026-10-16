#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/mysqlcppconn/sql/QueryMaker.h"

using namespace mysqli::sqlmaker;
using namespace testing;

class UTEST_QueryMaker : public Test
{
 public:
  QueryMaker qmaker;
};

TEST_F(UTEST_QueryMaker, date_query)
{
  EXPECT_EQ(qmaker.make_date_query(), "SELECT CURDATE();");
}

TEST_F(UTEST_QueryMaker, date_query_is_stable)
{
  EXPECT_EQ(&qmaker.make_date_query(), &qmaker.make_date_query());
}
