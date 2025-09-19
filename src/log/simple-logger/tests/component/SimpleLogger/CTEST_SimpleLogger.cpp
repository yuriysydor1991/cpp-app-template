#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <functional>
#include <set>
#include <string>
#include <thread>

#include "src/log/simple-logger/SimpleLogger.h"

using namespace testing;
using namespace simple_logger;

class CTEST_SimpleLogger : public Test
{
 public:
  inline static const std::string test_default_log_file =
      CTEST_SimpleLogger_DATA_DIR "/CTEST_SimpleLogger.log";
  inline static const unsigned short& default_log_level =
      SimpleLogger::LVL_TRACE;

  CTEST_SimpleLogger() { clear_default_log_file(); }
  ~CTEST_SimpleLogger() { clear_default_log_file(); }

  void default_log_lvl_init(const unsigned short& lvl)
  {
    SimpleLogger::init(test_default_log_file, lvl, true);
  }

  void default_log_init(const bool print = true)
  {
    SimpleLogger::init(test_default_log_file, default_log_level, print);
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
    std::fstream log{test_default_log_file.c_str(),
                     std::fstream::out | std::fstream::trunc};

    log.close();
  }

  const std::set<unsigned short> levelsSet{
      SimpleLogger::LVL_ERROR, SimpleLogger::LVL_WARNING,
      SimpleLogger::LVL_INFO, SimpleLogger::LVL_DEBUG, SimpleLogger::LVL_TRACE};
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
    auto cval = *iter;
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

  EXPECT_FALSE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

TEST_F(CTEST_SimpleLogger, error_with_max_warning_log_present)
{
  static const std::string expect = "expect present";

  default_log_lvl_init(SimpleLogger::LVL_WARNING);

  SimpleLogger::log(SimpleLogger::LVL_ERROR, expect);

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

TEST_F(CTEST_SimpleLogger, multithread_logs)
{
  static constexpr const unsigned int iters_per_thread = 1000U;

  default_log_init(false);

  std::set<std::shared_ptr<std::thread>> ths;

  const auto concurencyLog = []() {
    for (auto jter = 0U; jter < iters_per_thread; ++jter) {
      SimpleLogger::log(SimpleLogger::LVL_ERROR,
                        "Concurency thread log msg #" + std::to_string(jter));
    }
  };

  for (auto iter = 0U; iter < std::thread::hardware_concurrency(); ++iter) {
    ths.insert(std::make_shared<std::thread>(concurencyLog));
  }

  for (auto& th : ths) {
    if (th->joinable()) {
      th->join();
    }
  }

  ths.clear();

  auto logs = get_default_log_file_contents();

  const unsigned int expectedLogsLines =
      std::thread::hardware_concurrency() * iters_per_thread;

  const auto newlines = std::count_if(logs.begin(), logs.end(),
                                      [](const char& c) { return c == '\n'; });

  EXPECT_EQ(newlines, expectedLogsLines);

  while (!logs.empty()) {
    auto lineEnd = std::find(logs.begin(), logs.end(), '\n');

    std::string line{logs.begin(), lineEnd};

    if (lineEnd < logs.end()) {
      lineEnd++;
    }

    logs.erase(logs.begin(), lineEnd);

    EXPECT_THAT(line, ContainsRegex(" Concurency thread log msg #[0-9]{1,3}$"));
  }
}
