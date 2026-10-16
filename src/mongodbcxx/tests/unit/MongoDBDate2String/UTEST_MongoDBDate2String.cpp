#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <ctime>

#include "src/mongodbcxx/converters/MongoDBDate2String.h"
#include "src/mongodbcxx/mongocxx-includes.h"

using namespace mongodbcxxi::converters;
using namespace testing;

class UTEST_MongoDBDate2String : public Test
{
 public:
  UTEST_MongoDBDate2String()
  {
    // the converter formats the local time
    setenv("TZ", "UTC", 1);
    tzset();
  }

  static bsoncxx::types::b_date make_date(const std::int64_t millis)
  {
    return bsoncxx::types::b_date{std::chrono::milliseconds{millis}};
  }
};

TEST_F(UTEST_MongoDBDate2String, converts_into_the_iso_date)
{
  // 2025-05-31T12:00:00Z
  EXPECT_EQ(MongoDBDate2String::convert(make_date(1748692800000)),
            "2025-05-31");
}

TEST_F(UTEST_MongoDBDate2String, converts_the_epoch)
{
  EXPECT_EQ(MongoDBDate2String::convert(make_date(0)), "1970-01-01");
}

TEST_F(UTEST_MongoDBDate2String, last_millisecond_of_the_day)
{
  // 2026-10-16T23:59:59.999Z
  EXPECT_EQ(MongoDBDate2String::convert(make_date(1792195199999)),
            "2026-10-16");
}
