#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>

#include "GlobalLocaleGuard.h"
#include "GroupingNumpunct.h"
#include "src/log/ILogger.h"
#include "src/log/default-logger/DefaultLogger.h"
#include "src/log/default-logger/real-default-logger/RealDefaultLogger.h"

using namespace testing;
using namespace default_logger;

class CTEST_DefaultLogger : public Test
{
 public:
  inline static const std::string test_default_log_file =
      CTEST_DefaultLogger_DATA_DIR "/CTEST_DefaultLogger.log";
  inline static const unsigned short& default_log_level =
      DefaultLogger::LVL_TRACE;

  CTEST_DefaultLogger() { clear_default_log_file(); }
  ~CTEST_DefaultLogger() { clear_default_log_file(); }

  void default_log_lvl_init(const unsigned short& lvl)
  {
    DefaultLogger::init(test_default_log_file, lvl, true);
  }

  void default_log_init(const bool print = true)
  {
    DefaultLogger::init(test_default_log_file, default_log_level, print);
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

  /**
   * @brief Only the WARNING severity and above is flushed, so a lower severity
   * message is absent from the log file even when it is logged. The ERROR
   * sentinel flushes whatever was logged in front of it, which makes the
   * absence of the dropped message a proof of the level filter.
   */
  void expect_dropped(const std::string& dropped)
  {
    static const std::string sentinel = "the flushing error sentinel";

    DefaultLogger::log(DefaultLogger::LVL_ERROR, sentinel);

    const auto logs = get_default_log_file_contents();

    EXPECT_THAT(logs, EndsWith(sentinel + "\n"));
    EXPECT_THAT(logs, Not(HasSubstr(dropped)));
  }

  const std::set<unsigned short> levelsSet{
      DefaultLogger::LVL_ERROR, DefaultLogger::LVL_WARNING,
      DefaultLogger::LVL_INFO, DefaultLogger::LVL_DEBUG,
      DefaultLogger::LVL_TRACE};
};

TEST_F(CTEST_DefaultLogger, nonempty_defaultLogDateFormat)
{
  EXPECT_FALSE(std::string{DefaultLogger::defaultLogDateFormat}.empty());
}

TEST_F(CTEST_DefaultLogger, nonempty_default_log_name)
{
  EXPECT_FALSE(DefaultLogger::default_log_name.empty());
}

TEST_F(CTEST_DefaultLogger, no_equal_levels)
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

TEST_F(CTEST_DefaultLogger, first_error_log)
{
  static const std::string test_str = "first log test 0123-";

  default_log_init();

  DefaultLogger::log(DefaultLogger::LVL_ERROR, test_str);

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());

  EXPECT_THAT(logs, EndsWith(test_str + "\n"));
}

TEST_F(CTEST_DefaultLogger, trace_with_max_debug_log_absent)
{
  default_log_lvl_init(DefaultLogger::LVL_DEBUG);

  DefaultLogger::log(DefaultLogger::LVL_TRACE, "Expect absent");

  expect_dropped("Expect absent");
}

TEST_F(CTEST_DefaultLogger, debug_with_max_info_log_absent)
{
  default_log_lvl_init(DefaultLogger::LVL_INFO);

  DefaultLogger::log(DefaultLogger::LVL_DEBUG, "Expect absent");

  expect_dropped("Expect absent");
}

TEST_F(CTEST_DefaultLogger, info_with_max_warning_log_absent)
{
  default_log_lvl_init(DefaultLogger::LVL_WARNING);

  DefaultLogger::log(DefaultLogger::LVL_INFO, "Expect absent");

  expect_dropped("Expect absent");
}

TEST_F(CTEST_DefaultLogger, warning_with_max_error_log_absent)
{
  default_log_lvl_init(DefaultLogger::LVL_ERROR);

  DefaultLogger::log(DefaultLogger::LVL_WARNING, "Expect absent");

  expect_dropped("Expect absent");
}

TEST_F(CTEST_DefaultLogger, warning_with_max_info_log_present)
{
  static const std::string expect = "expect present";

  default_log_lvl_init(DefaultLogger::LVL_INFO);

  DefaultLogger::log(DefaultLogger::LVL_WARNING, expect);

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

TEST_F(CTEST_DefaultLogger, error_with_max_warning_log_present)
{
  static const std::string expect = "expect present";

  default_log_lvl_init(DefaultLogger::LVL_WARNING);

  DefaultLogger::log(DefaultLogger::LVL_ERROR, expect);

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

TEST_F(CTEST_DefaultLogger, unopenable_log_file_is_reported_without_throwing)
{
  static const std::string missingDirLog =
      CTEST_DefaultLogger_DATA_DIR "/no-such-directory/CTEST_DefaultLogger.log";

  EXPECT_FALSE(
      DefaultLogger::init(missingDirLog, DefaultLogger::LVL_TRACE, false));
  EXPECT_NO_THROW(DefaultLogger::log(DefaultLogger::LVL_ERROR, "no file"));

  EXPECT_TRUE(DefaultLogger::init(test_default_log_file,
                                  DefaultLogger::LVL_TRACE, false));
}

TEST_F(CTEST_DefaultLogger, unwritable_default_log_file_gives_a_warning_only)
{
  namespace fs = std::filesystem;

  // Nobody, the root included, creates files in the /proc directory.
  static const fs::path readOnlyDir{"/proc"};

  if (!fs::is_directory(readOnlyDir) ||
      fs::path{RealDefaultLogger::get_default_full_log_path()}.is_absolute()) {
    GTEST_SKIP() << "No read only directory for the relative default log";
  }

  const fs::path previousDir = fs::current_path();
  std::ostringstream captured;
  std::streambuf* const previousCerr = std::cerr.rdbuf(captured.rdbuf());

  fs::current_path(readOnlyDir);

  EXPECT_NO_THROW(DefaultLogger::init_defaults());

  fs::current_path(previousDir);
  std::cerr.rdbuf(previousCerr);

  EXPECT_THAT(captured.str(), HasSubstr("logging into the console only"));
  EXPECT_FALSE(fs::exists(readOnlyDir / DefaultLogger::default_log_name));
}

TEST_F(CTEST_DefaultLogger, multithread_logs)
{
  static constexpr const unsigned int iters_per_thread = 1000U;

  default_log_init(false);

  std::set<std::shared_ptr<std::thread>> ths;

  const auto concurencyLog = []() {
    for (auto jter = 0U; jter < iters_per_thread; ++jter) {
      DefaultLogger::log(DefaultLogger::LVL_ERROR,
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

TEST_F(CTEST_DefaultLogger, log_fields_ignore_the_application_global_locale)
{
  const GlobalLocaleGuard localeGuard{
      std::locale{std::locale::classic(), new GroupingNumpunct}};

  default_log_init();

  // The error level is flushed into the log file straight away.
  DefaultLogger::log(DefaultLogger::LVL_ERROR, "the message");

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());

  // The thread id and the microseconds are the logger own numeric fields. They
  // must never carry the digit group separators of the application locale.
  EXPECT_THAT(logs, Not(HasSubstr(",")));
  EXPECT_THAT(logs, ContainsRegex(" ERR [0-9]+ the message"));
}

TEST_F(CTEST_DefaultLogger, log_message_stream_fill_is_not_sticky)
{
  default_log_init();

  DefaultLogger::log(DefaultLogger::LVL_ERROR, "the message");

  const auto logs = get_default_log_file_contents();

  EXPECT_FALSE(logs.empty());

  // The timestamp sets a zero fill character for its microseconds field. It
  // must not stay behind and pad any later field of the very same message.
  EXPECT_THAT(logs, Not(ContainsRegex("ERR 0+[0-9]* the message")));
}
