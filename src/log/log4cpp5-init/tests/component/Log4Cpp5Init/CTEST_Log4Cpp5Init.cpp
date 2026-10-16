#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <string>

#include "src/log/log4cpp5-init/Log4Cpp5Init.h"

using namespace log4cpp5i;
using namespace testing;

class CTEST_Log4Cpp5Init : public Test
{
 public:
  inline static const std::string test_log_file =
      CTEST_Log4Cpp5Init_DATA_DIR "/CTEST_Log4Cpp5Init.log";
  inline static const std::string unopenable_log_file =
      "/nonexistent-directory/CTEST_Log4Cpp5Init.log";

  static log4cpp::AppenderSet appenders()
  {
    return log4cpp::Category::getRoot().getAllAppenders();
  }

  static bool is_console(log4cpp::Appender* appender)
  {
    return dynamic_cast<log4cpp::OstreamAppender*>(appender) != nullptr;
  }
};

TEST_F(CTEST_Log4Cpp5Init, repeated_init_replaces_the_appenders)
{
  Log4Cpp5Init::init(test_log_file, MACRO_LVL_ERROR, true);
  Log4Cpp5Init::init(test_log_file, MACRO_LVL_ERROR, true);

  EXPECT_EQ(appenders().size(), 2U);
}

TEST_F(CTEST_Log4Cpp5Init, no_printing_leaves_the_file_appender_only)
{
  Log4Cpp5Init::init(test_log_file, MACRO_LVL_ERROR, true);
  Log4Cpp5Init::init(test_log_file, MACRO_LVL_ERROR, false);

  const auto all = appenders();

  ASSERT_EQ(all.size(), 1U);
  EXPECT_FALSE(is_console(*all.begin()));
}

TEST_F(CTEST_Log4Cpp5Init, unopenable_log_file_falls_back_to_the_stdout)
{
  internal::CaptureStderr();

  Log4Cpp5Init::init(unopenable_log_file, MACRO_LVL_ERROR, false);

  EXPECT_THAT(internal::GetCapturedStderr(), HasSubstr(unopenable_log_file));

  const auto all = appenders();

  ASSERT_EQ(all.size(), 1U);
  EXPECT_TRUE(is_console(*all.begin()));
}

TEST_F(CTEST_Log4Cpp5Init, project_levels_map_onto_the_log4cpp_priorities)
{
  EXPECT_EQ(Log4Cpp5Init::get_log4cpp_priority(MACRO_LVL_ERROR),
            log4cpp::Priority::ERROR);
  EXPECT_EQ(Log4Cpp5Init::get_log4cpp_priority(MACRO_LVL_WARNING),
            log4cpp::Priority::WARN);
  EXPECT_EQ(Log4Cpp5Init::get_log4cpp_priority(MACRO_LVL_INFO),
            log4cpp::Priority::INFO);
  EXPECT_EQ(Log4Cpp5Init::get_log4cpp_priority(MACRO_LVL_DEBUG),
            log4cpp::Priority::DEBUG);
  EXPECT_EQ(Log4Cpp5Init::get_log4cpp_priority(MACRO_LVL_TRACE),
            Log4Cpp5Init::trace_priority);
}

TEST_F(CTEST_Log4Cpp5Init, trace_is_dropped_at_the_debug_level)
{
  Log4Cpp5Init::init(test_log_file, MACRO_LVL_DEBUG, false);

  const log4cpp::Category& root = log4cpp::Category::getRoot();

  EXPECT_TRUE(root.isPriorityEnabled(log4cpp::Priority::DEBUG));
  EXPECT_FALSE(root.isPriorityEnabled(Log4Cpp5Init::trace_priority));
}
