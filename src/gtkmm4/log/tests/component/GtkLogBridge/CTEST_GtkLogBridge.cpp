// The GLib takes this very name as the domain of every message this test
// reports, the way an application names it's own domain. It has to stand
// before the very first GLib header of the translation unit.
#define G_LOG_DOMAIN "CTEST_GtkLogBridge"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "src/gtkmm4/log/GtkLogBridge.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace testing;
using namespace Gtkmm4i::gtklog;

/**
 * @brief Component test of the toolkit messages bridge: the real GtkLogBridge
 * over the real GLib logging, with the real application logger behind it, so
 * every case is measured in the log file itself and not in a mock.
 *
 * The bridge is installed once for the whole binary by the own main below,
 * because the GLib accepts a writer only once in the life of a process.
 */
class CTEST_GtkLogBridge : public Test
{
 public:
  inline static const std::string test_log_file =
      CTEST_GtkLogBridge_DATA_DIR "/CTEST_GtkLogBridge.log";

  CTEST_GtkLogBridge() { clear_log_file(); }
  ~CTEST_GtkLogBridge() override { clear_log_file(); }

  void SetUp() override { LOG_INIT(test_log_file, MACRO_LVL_TRACE, false); }

  std::string log_contents()
  {
    // The logging facade exposes no flush of it's own, and the logger is only
    // required to flush the warnings and the errors by itself, so the log file
    // is reopened - which closes it first - to bring the lower severities into
    // the filesystem as well.
    LOG_INIT(test_log_file, MACRO_LVL_TRACE, false);

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

  /**
   * @brief Tells whether the toolkit reports it's info and debug messages at
   * all, which the G_MESSAGES_DEBUG variable of the environment decides. The
   * GLib reads that variable once in the life of a process, so a test can not
   * switch the toolkit chatter on or off for itself.
   */
  static bool toolkit_chatter_switched_on()
  {
    return g_getenv("G_MESSAGES_DEBUG") != nullptr;
  }
};

TEST_F(CTEST_GtkLogBridge, warning_reaches_the_log_as_a_warning)
{
  g_warning("a toolkit warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" WRN "));
  EXPECT_THAT(logs, HasSubstr(G_LOG_DOMAIN ": "));
  EXPECT_THAT(logs, HasSubstr("a toolkit warning of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, critical_reaches_the_log_as_an_error)
{
  // The GLib critical level stands for a broken invariant, the very way it's
  // error one does, so both of them are errors of the application log.
  g_critical("a toolkit critical of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" ERR "));
  EXPECT_THAT(logs, HasSubstr("a toolkit critical of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, message_reaches_the_log_as_an_info)
{
  g_message("a toolkit message of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" INF "));
  EXPECT_THAT(logs, HasSubstr("a toolkit message of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, log_line_names_the_toolkit_source_of_the_message)
{
  // The GTK is built with the structured GLib logging, so every message of it
  // carries the source file, the line and the function which reported it. The
  // very same fields are given here by hand, because a g_warning of a project
  // which is not built that way carries none of them - and the bridge keeps
  // all three of them in the message text, with the file name alone of the
  // toolkit path.
  g_log_structured(G_LOG_DOMAIN, G_LOG_LEVEL_WARNING, "CODE_FILE",
                   "/the/toolkit/source/gtkwidget.c", "CODE_LINE", "512",
                   "CODE_FUNC", "gtk_widget_measure", "MESSAGE",
                   "a located warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("gtkwidget.c:512: gtk_widget_measure: "));
  EXPECT_THAT(logs, Not(HasSubstr("/the/toolkit/source/")));
  EXPECT_THAT(logs, HasSubstr("a located warning of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, printed_text_reaches_the_log_as_an_info)
{
  g_print("a g_print line of the bridge test\n");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" INF "));
  EXPECT_THAT(logs, HasSubstr("GLib print: a g_print line of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, printed_error_text_reaches_the_log_as_a_warning)
{
  g_printerr("a g_printerr line of the bridge test\n");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" WRN "));
  EXPECT_THAT(logs,
              HasSubstr("GLib print: a g_printerr line of the bridge test"));
}

TEST_F(CTEST_GtkLogBridge, printed_text_keeps_a_single_line_in_the_log)
{
  // The g_print and the g_printerr texts carry the line ending of a terminal
  // stream, and the logger appends an own one to every message it receives.
  g_print("a single line of the bridge test\n");

  const std::string logs = log_contents();

  EXPECT_EQ(logs.find("\n\n"), std::string::npos);
}

TEST_F(CTEST_GtkLogBridge, debug_message_is_dropped_while_the_domain_is_off)
{
  if (toolkit_chatter_switched_on()) {
    GTEST_SKIP() << "The G_MESSAGES_DEBUG of the environment reports the "
                    "toolkit debug messages";
  }

  // Without the G_MESSAGES_DEBUG variable the toolkit debug traffic stays out
  // of the log, the very way it does with the default GLib writer. That is the
  // behaviour of every GTK application and the bridge must not change it.
  g_debug("a toolkit debug message of the bridge test");

  EXPECT_THAT(log_contents(),
              Not(HasSubstr("a toolkit debug message of the bridge test")));
}

TEST_F(CTEST_GtkLogBridge, debug_message_reaches_the_log_while_the_domain_is_on)
{
  if (!toolkit_chatter_switched_on()) {
    GTEST_SKIP() << "The G_MESSAGES_DEBUG of the environment drops the "
                    "toolkit debug messages";
  }

  g_debug("a switched on debug message of the bridge test");

  const std::string logs = log_contents();

#if MAX_LOG_LEVEL >= MACRO_LVL_DEBUG
  EXPECT_THAT(logs, HasSubstr(" DBG "));
  EXPECT_THAT(logs,
              HasSubstr("a switched on debug message of the bridge test"));
#else
  // A build which does not keep it's own debug messages drops the toolkit ones
  // as well, whatever the G_MESSAGES_DEBUG variable says.
  EXPECT_THAT(logs,
              Not(HasSubstr("a switched on debug message of the bridge test")));
#endif  // MAX_LOG_LEVEL
}

TEST_F(CTEST_GtkLogBridge, repeated_install_is_ignored)
{
  // The GLib kills the process on a second g_log_set_writer_func call, so the
  // survival of this test is the measurement itself.
  GtkLogBridge::install();
  GtkLogBridge::install();

  g_warning("a warning after the repeated install");

  EXPECT_THAT(log_contents(),
              HasSubstr("a warning after the repeated install"));
}

int main(int argc, char** argv)
{
  // The application has it's logger ready before the toolkit is touched, and
  // the GLib logging is taken over right after that, exactly the way the
  // GtkmmIniter does it. Both happen once for the whole binary, because the
  // GLib accepts a writer only once in the life of a process.
  LOG_INIT(CTEST_GtkLogBridge::test_log_file, MACRO_LVL_TRACE, false);

  GtkLogBridge::install();

  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
