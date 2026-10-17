#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "src/plplot/PLplotDevicePicker.h"

using namespace plploti;
using namespace testing;

class UTEST_PLplotDevicePicker : public Test
{
 public:
  PLplotDevicePicker picker;
};

TEST_F(UTEST_PLplotDevicePicker, the_qt_device_goes_first)
{
  EXPECT_EQ(picker.pick({"xwin", "svg", "xcairo", "qtwidget"}), "qtwidget");
}

TEST_F(UTEST_PLplotDevicePicker,
       the_next_preferred_device_replaces_a_missing_one)
{
  EXPECT_EQ(picker.pick({"null", "xwin", "svg", "xcairo"}), "xcairo");
  EXPECT_EQ(picker.pick({"null", "xwin", "svg"}), "xwin");
}

TEST_F(UTEST_PLplotDevicePicker, no_interactive_device_gives_none)
{
  EXPECT_TRUE(picker.pick({"null", "svg", "ps", "mem"}).empty());
  EXPECT_TRUE(picker.pick({}).empty());
}

TEST_F(UTEST_PLplotDevicePicker, a_device_name_prefix_is_no_match)
{
  EXPECT_TRUE(picker.pick({"qt", "xcairo2", "x"}).empty());
}
