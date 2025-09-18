#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <fstream>

#include "src/log/simple-logger/SimpleLogger.h"

using namespace testing;
using namespace simple_logger;

class CTEST_SimpleLogger : public Test
{
 public:
  inline static const std::string test_default_log_file = CTEST_SimpleLogger_DATA_DIR "/CTEST_SimpleLogger.log";
  inline static const unsigned short& default_log_level = SimpleLogger::LVL_TRACE;
  
 CTEST_SimpleLogger() { clear_default_log_file(); }
 ~CTEST_SimpleLogger() { clear_default_log_file(); }
 
 void default_log_lvl_init(const unsigned short& lvl)
 {
  SimpleLogger::init(test_default_log_file,
                     lvl,
                     true);
 }
  
 void default_log_init()
 {
  SimpleLogger::init(test_default_log_file,
                   default_log_level,
                   true);
 }
 
 std::string get_default_log_file_contents()
 {
   std::fstream log{test_default_log_file.c_str(), std::fstream::in};
   
   std::string rt;
   char c{0};
   
   while (log.get(c)) {
    rt += c;
   }
  
   log.close();
   
   return rt;
 }
  
 void clear_default_log_file()
 {
  std::fstream log{test_default_log_file.c_str(), std::fstream::out | std::fstream::trunc};
  
  log.close();
 }
  
 const std::set<unsigned short> levelsSet{
  SimpleLogger::LVL_ERROR,
  SimpleLogger::LVL_WARNING,
  SimpleLogger::LVL_INFO,
  SimpleLogger::LVL_DEBUG,
  SimpleLogger::LVL_TRACE
 };
};

TEST_F(CTEST_SimpleLogger, nonempty_defaultLogDateFormat)
{
  EXPECT_FALSE(std::string{SimpleLogger::defaultLogDateFormat}.empty());
}

TEST_F(CTEST_SimpleLogger, nonempty_default_log_name)
{
  EXPECT_FALSE(SimpleLogger::default_log_name.empty());
}

TEST_F(CTEST_SimpleLogger, no_equal_levels)
{
  EXPECT_GE(levelsSet.size(), 5U);
  
  for (auto iter = levelsSet.begin(); iter != levelsSet.end(); ++iter) {
    auto cval = *iter ;
    auto next = iter;
    for (auto jter = ++next; jter != levelsSet.end(); ++jter) {
      EXPECT_NE(*jter, cval);
    }
  }
}

TEST_F(CTEST_SimpleLogger, first_error_log)
{
  static const std::string test_str = "first log test 0123-";
  
  default_log_init();
  
  SimpleLogger::log(SimpleLogger::LVL_ERROR, test_str);
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_FALSE(logs.empty());
  
  EXPECT_THAT(logs, EndsWith(test_str + "\n"));
}

TEST_F(CTEST_SimpleLogger, trace_with_max_debug_log_absent)
{  
  default_log_lvl_init(SimpleLogger::LVL_DEBUG);
  
  SimpleLogger::log(SimpleLogger::LVL_TRACE, "Expect absent");
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_TRUE(logs.empty());
  EXPECT_EQ(logs, std::string{});
}

TEST_F(CTEST_SimpleLogger, debug_with_max_info_log_absent)
{  
  default_log_lvl_init(SimpleLogger::LVL_INFO);
  
  SimpleLogger::log(SimpleLogger::LVL_DEBUG, "Expect absent");
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_TRUE(logs.empty());
  EXPECT_EQ(logs, std::string{});
}

TEST_F(CTEST_SimpleLogger, info_with_max_warning_log_absent)
{  
  default_log_lvl_init(SimpleLogger::LVL_WARNING);
  
  SimpleLogger::log(SimpleLogger::LVL_INFO, "Expect absent");
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_TRUE(logs.empty());
  EXPECT_EQ(logs, std::string{});
}

TEST_F(CTEST_SimpleLogger, warning_with_max_error_log_absent)
{  
  default_log_lvl_init(SimpleLogger::LVL_ERROR);
  
  SimpleLogger::log(SimpleLogger::LVL_WARNING, "Expect absent");
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_TRUE(logs.empty());
  EXPECT_EQ(logs, std::string{});
}

TEST_F(CTEST_SimpleLogger, warning_with_max_info_log_present)
{
  static const std::string expect = "expect present";
  
  default_log_lvl_init(SimpleLogger::LVL_INFO);
  
  SimpleLogger::log(SimpleLogger::LVL_WARNING, expect);
  
  const auto logs = get_default_log_file_contents();
  
  EXPECT_TRUE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

