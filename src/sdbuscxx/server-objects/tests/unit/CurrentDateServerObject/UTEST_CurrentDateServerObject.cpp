#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cctype>
#include <cstddef>
#include <ctime>
#include <functional>
#include <string>

#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"

using namespace testing;
using namespace sdbuscxxi;

namespace
{

/// @brief 2021-01-01 00:00:00 UTC.
constexpr std::time_t kKnownTimestamp = 1609459200;

/**
 * @brief Test double exposing the now() seam so current_date() is deterministic.
 */
class TestableCurrentDateServerObject : public CurrentDateServerObject
{
 public:
  std::function<std::time_t()> onNow;

 protected:
  std::time_t now() override
  {
    return onNow ? onNow() : CurrentDateServerObject::now();
  }
};

void expect_iso_date(const std::string& date)
{
  ASSERT_EQ(date.size(), 10U);
  EXPECT_EQ(date[4], '-');
  EXPECT_EQ(date[7], '-');
  for (std::size_t i : {0U, 1U, 2U, 3U, 5U, 6U, 8U, 9U}) {
    EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(date[i])))
        << "non-digit at index " << i << " of '" << date << "'";
  }
}

}  // namespace

class UTEST_CurrentDateServerObject : public Test
{
 public:
  TestableCurrentDateServerObject object;
};

TEST_F(UTEST_CurrentDateServerObject, format_date_epoch)
{
  EXPECT_EQ(CurrentDateServerObject::format_date(0), "1970-01-01");
}

TEST_F(UTEST_CurrentDateServerObject, format_date_known_timestamp)
{
  EXPECT_EQ(CurrentDateServerObject::format_date(kKnownTimestamp), "2021-01-01");
}

TEST_F(UTEST_CurrentDateServerObject, current_date_has_iso_format)
{
  expect_iso_date(object.current_date());
}

TEST_F(UTEST_CurrentDateServerObject, current_date_uses_now_seam)
{
  object.onNow = []() { return kKnownTimestamp; };

  EXPECT_EQ(object.current_date(), "2021-01-01");
}

TEST_F(UTEST_CurrentDateServerObject, exposes_expected_well_known_coordinates)
{
  EXPECT_EQ(static_cast<std::string>(CurrentDateServerObject::serviceName),
            "org.cppapptemplate.SimpleServer");
  EXPECT_EQ(static_cast<std::string>(CurrentDateServerObject::objectPath),
            "/org/cppapptemplate/SimpleServer");
  EXPECT_EQ(static_cast<std::string>(CurrentDateServerObject::interfaceName),
            "org.cppapptemplate.SimpleServer1");
  EXPECT_EQ(
      static_cast<std::string>(CurrentDateServerObject::currentDateProperty),
      "CurrentDate");
}

TEST_F(UTEST_CurrentDateServerObject, accessors_return_well_known_coordinates)
{
  EXPECT_EQ(object.service_name(), CurrentDateServerObject::serviceName);
  EXPECT_EQ(object.object_path(), CurrentDateServerObject::objectPath);
}
