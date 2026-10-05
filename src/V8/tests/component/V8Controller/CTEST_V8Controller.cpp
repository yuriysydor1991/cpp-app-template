#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

#include "src/V8/V8Controller.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace v8i;
using namespace testing;

class CTEST_V8Controller : public Test
{
 public:
  CTEST_V8Controller()
  {
    std::ofstream truncating{logFile, std::ofstream::trunc};

    LOG_INIT(logFile, MACRO_LVL_TRACE, false);
  }

  /// @brief Reopens the log file to flush it, since the logger flushes the
  /// warnings and the errors alone, and gives the log written so far.
  std::string log_contents() const
  {
    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    std::stringstream contents;

    contents << std::ifstream{logFile}.rdbuf();

    return contents.str();
  }

  /// @brief Gives the pattern of the log line of the given level coming from
  /// the given JavaScript location.
  static std::string line_of(const unsigned short level,
                             const std::string& location,
                             const std::string& message)
  {
    return LOG_REAL_LOGGER()->lvl_repr(level) + " .* " + location + " : " +
           message;
  }

  /// @brief Every test case gets a log file of it's own, so the parallel
  /// ctest runs keep their logs apart.
  const std::string logFile{
      std::string{CTEST_V8Controller_DATA_DIR "/"} +
      UnitTest::GetInstance()->current_test_info()->name() + ".log"};

  V8ControllerPtr controller{V8Controller::create()};
};

TEST_F(CTEST_V8Controller, console_log_writes_into_the_project_log)
{
  ASSERT_TRUE(controller->init({}));
  ASSERT_TRUE(controller->run("console.log('Hello, V8!', 1 + 2)", "hello.js"));

  EXPECT_THAT(
      log_contents(),
      ContainsRegex(line_of(MACRO_LVL_INFO, "hello\\.js:1", "Hello, V8! 3")));
}

TEST_F(CTEST_V8Controller, console_methods_log_at_their_levels)
{
  ASSERT_TRUE(controller->init({}));
  ASSERT_TRUE(
      controller->run("console.info('info');\n"
                      "console.warn('warn');\n"
                      "console.error('error');\n"
                      "console.debug('debug');\n"
                      "console.trace('trace');",
                      "levels.js"));

  const auto logs = log_contents();

  EXPECT_THAT(logs,
              ContainsRegex(line_of(MACRO_LVL_INFO, "levels\\.js:1", "info")));
  EXPECT_THAT(
      logs, ContainsRegex(line_of(MACRO_LVL_WARNING, "levels\\.js:2", "warn")));
  EXPECT_THAT(
      logs, ContainsRegex(line_of(MACRO_LVL_ERROR, "levels\\.js:3", "error")));
  EXPECT_THAT(
      logs, ContainsRegex(line_of(MACRO_LVL_DEBUG, "levels\\.js:4", "debug")));
  EXPECT_THAT(
      logs, ContainsRegex(line_of(MACRO_LVL_TRACE, "levels\\.js:5", "trace")));
}

TEST_F(CTEST_V8Controller, logger_level_filters_the_console)
{
  ASSERT_TRUE(controller->init({}));

  LOG_INIT(logFile, MACRO_LVL_WARNING, false);

  ASSERT_TRUE(controller->run("console.log('dropped'); console.warn('kept')",
                              "filter.js"));

  const auto logs = log_contents();

  EXPECT_THAT(logs, Not(HasSubstr("dropped")));
  EXPECT_THAT(logs, HasSubstr("filter.js:1 : kept"));
}

TEST_F(CTEST_V8Controller, promise_callbacks_run_after_the_script)
{
  ASSERT_TRUE(controller->init({}));
  ASSERT_TRUE(controller->run(
      "Promise.resolve(7).then(v => console.log('resolved', v))", "async.js"));

  EXPECT_THAT(log_contents(), HasSubstr("async.js:1 : resolved 7"));
}

TEST_F(CTEST_V8Controller, run_returns_the_completion_value)
{
  ASSERT_TRUE(controller->init({}));

  EXPECT_EQ(controller->run("6 * 7", "value.js"), "42");
  EXPECT_EQ(controller->run("[1, 2, 3].map(v => v * 2)", "value.js"), "2,4,6");
}

TEST_F(CTEST_V8Controller, internationalization_is_available)
{
  ASSERT_TRUE(controller->init({}));

  EXPECT_EQ(controller->run("new Intl.NumberFormat('en-US').format(1234.5)",
                            "intl.js"),
            "1,234.5");
}

TEST_F(CTEST_V8Controller, globals_survive_between_runs)
{
  ASSERT_TRUE(controller->init({}));
  ASSERT_TRUE(controller->run("var answer = 40", "first.js"));

  EXPECT_EQ(controller->run("answer + 2", "second.js"), "42");
}

TEST_F(CTEST_V8Controller, controllers_keep_their_globals_apart)
{
  auto another = V8Controller::create();

  ASSERT_TRUE(controller->init({}));
  ASSERT_TRUE(another->init({}));
  ASSERT_TRUE(controller->run("var answer = 42", "first.js"));

  EXPECT_EQ(another->run("typeof answer", "second.js"), "undefined");
}

TEST_F(CTEST_V8Controller, syntax_error_is_logged_with_its_location)
{
  ASSERT_TRUE(controller->init({}));

  EXPECT_FALSE(controller->run("let = ;", "broken.js").has_value());

  EXPECT_THAT(log_contents(), ContainsRegex("broken\\.js:1 : .*SyntaxError"));
}

TEST_F(CTEST_V8Controller, thrown_error_is_logged_with_its_location)
{
  ASSERT_TRUE(controller->init({}));

  EXPECT_FALSE(controller->run("\n\nthrow new Error('boom')", "throwing.js")
                   .has_value());

  EXPECT_THAT(log_contents(),
              HasSubstr("throwing.js:3 : Uncaught Error: boom"));
}

TEST_F(CTEST_V8Controller, run_before_init_fails)
{
  EXPECT_FALSE(controller->run("1 + 2", "early.js").has_value());
}
