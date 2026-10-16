#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <thread>

#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace testing;

/**
 * @brief Component test for the top-level log.h facilities (the LOG_INIT and
 * LOGx macros), exercised through the public facade only - it never names a
 * concrete logger implementation, so the same source can be reused on the
 * branches that swap the underlying logger (appLog4Cpp5, appBoostBeast, ...).
 *
 * The runtime level (the second LOG_INIT argument) is driven through the
 * branch-agnostic MACRO_LVL_* severities. The facade exposes no flush and a
 * logger is only required to flush at the WARNING severity or above, so a
 * lower severity message is absent from the log file even when it is logged.
 * That is why every dropped message is followed by an ERROR sentinel, which
 * flushes whatever was logged in front of it: the sentinel must be present and
 * the dropped message absent.
 */
class CTEST_log : public Test
{
 public:
  inline static const std::string test_log_file =
      CTEST_log_DATA_DIR "/CTEST_log.log";

  CTEST_log() { clear_log_file(); }
  ~CTEST_log() { clear_log_file(); }

  void init(const unsigned short& level, const bool print = true)
  {
    LOG_INIT(test_log_file, level, print);
  }

  std::string log_contents()
  {
    std::fstream log{test_log_file.c_str(), std::fstream::in};

    std::string rt;
    char c{0};

    while (log.get(c)) {
      rt += c;
    }

    log.close();

    return rt;
  }

  void clear_log_file()
  {
    std::fstream log{test_log_file.c_str(),
                     std::fstream::out | std::fstream::trunc};

    log.close();
  }

  void expect_dropped(const std::string& dropped)
  {
    static const std::string sentinel = "the flushing error sentinel";

    LOGE(sentinel);

    const auto logs = log_contents();

    EXPECT_THAT(logs, EndsWith(sentinel + "\n"));
    EXPECT_THAT(logs, Not(HasSubstr(dropped)));
  }
};

TEST_F(CTEST_log, error_message_is_written)
{
  static const std::string expect = "facade error message 0123-";

  init(MACRO_LVL_ERROR);

  LOGE(expect);

  const auto logs = log_contents();

  EXPECT_FALSE(logs.empty());
  EXPECT_THAT(logs, EndsWith(expect + "\n"));
}

TEST_F(CTEST_log, warning_is_dropped_when_runtime_level_is_error)
{
  static const std::string dropped =
      "must be dropped at the error runtime level";

  init(MACRO_LVL_ERROR);

  LOGW(dropped);

  expect_dropped(dropped);
}

TEST_F(CTEST_log, warning_is_written_when_runtime_level_is_warning)
{
  static const std::string expect = "facade warning is present";

  if (MAX_LOG_LEVEL < MACRO_LVL_WARNING) {
    GTEST_SKIP() << "The LOGW macro is compiled out";
  }

  init(MACRO_LVL_WARNING);

  LOGW(expect);

  EXPECT_THAT(log_contents(), EndsWith(expect + "\n"));
}

TEST_F(CTEST_log, info_is_dropped_when_runtime_level_is_warning)
{
  static const std::string dropped =
      "must be dropped at the warning runtime level";

  init(MACRO_LVL_WARNING);

  LOGI(dropped);

  expect_dropped(dropped);
}

TEST_F(CTEST_log, debug_is_dropped_when_runtime_level_is_info)
{
  static const std::string dropped =
      "must be dropped at the info runtime level";

  init(MACRO_LVL_INFO);

  LOGD(dropped);

  expect_dropped(dropped);
}

TEST_F(CTEST_log, trace_is_dropped_when_runtime_level_is_debug)
{
  static const std::string dropped =
      "must be dropped at the debug runtime level";

  init(MACRO_LVL_DEBUG);

  LOGT(dropped);

  expect_dropped(dropped);
}

TEST_F(CTEST_log, macros_are_single_statements)
{
  static const std::string expect = "the else branch message";

  init(MACRO_LVL_TRACE);

  // Every macro must expand into a single statement, which an unbraced if and
  // else pair accepts, the compiled out ones included.
  if (test_log_file.empty()) LOGE("the if branch message");
  else
    LOGE(expect);

  if (test_log_file.empty()) LOGT("the if branch message");
  else
    LOGE(expect);

  EXPECT_THAT(log_contents(), EndsWith(expect + "\n"));
}

TEST_F(CTEST_log, multithread_error_logs)
{
  static constexpr const unsigned int iters_per_thread = 1000U;

  init(MACRO_LVL_ERROR, false);

  std::set<std::shared_ptr<std::thread>> ths;

  const auto concurencyLog = []() {
    for (auto jter = 0U; jter < iters_per_thread; ++jter) {
      LOGE("Concurency thread log msg #" + std::to_string(jter));
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

  auto logs = log_contents();

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
