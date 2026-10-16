#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/mongodbcxx/helpers/QueryMaker.h"
#include "src/mongodbcxx/mongocxx-includes.h"

using namespace mongodbcxxi::helpers;
using namespace testing;

class UTEST_QueryMaker : public Test
{
 public:
  static int command_value(const QueryMaker::JsonDoc& doc,
                           const std::string& command)
  {
    const auto element = doc.view()[command];

    return element ? element.get_int32().value : 0;
  }
};

TEST_F(UTEST_QueryMaker, ping_query_runs_the_ping_command)
{
  const auto doc = QueryMaker::create_ping_query();

  EXPECT_EQ(command_value(doc, "ping"), 1);
  EXPECT_EQ(std::distance(doc.view().begin(), doc.view().end()), 1);
}

TEST_F(UTEST_QueryMaker, date_query_runs_the_hello_command)
{
  const auto doc = QueryMaker::create_date_query();

  EXPECT_EQ(command_value(doc, "hello"), 1);
  EXPECT_EQ(std::distance(doc.view().begin(), doc.view().end()), 1);
}
