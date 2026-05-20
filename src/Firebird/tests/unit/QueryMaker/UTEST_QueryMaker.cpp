#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/Firebird/sql/QueryMaker.h"

using namespace firebirdi::sql;
using namespace testing;

class UTEST_QueryMaker : public Test
{
 public:
  UTEST_QueryMaker() : qmaker{std::make_shared<QueryMaker>(nullptr)} {}

  std::shared_ptr<QueryMaker> qmaker;
};

TEST_F(UTEST_QueryMaker, make_date_query_not_empty)
{
  EXPECT_FALSE(qmaker->make_date_query().empty());
}

TEST_F(UTEST_QueryMaker, make_date_query_is_firebird_dialect)
{
  const std::string query = qmaker->make_date_query();

  // Firebird requires a FROM clause even for scalar selects.
  EXPECT_THAT(query, HasSubstr("CURRENT_DATE"));
  EXPECT_THAT(query, HasSubstr("RDB$DATABASE"));
}
