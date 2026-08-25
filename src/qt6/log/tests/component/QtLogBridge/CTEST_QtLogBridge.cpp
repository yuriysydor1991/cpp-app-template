#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QLoggingCategory>
#include <QtGlobal>
#include <fstream>
#include <string>

#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"
#include "src/qt6/log/QtLogBridge.h"

using namespace testing;
using namespace Qt6i::qtlog;

namespace
{

/**
 * @brief A named logging category of this test, which stands for the named
 * ones of the toolkit modules - the qt.qml.import, the qt.quick.mouse and the
 * rest of them. It does not start with the qt prefix, so the toolkit keeps
 * it's debug messages switched on by default the way it does for every
 * category of an application.
 */
Q_LOGGING_CATEGORY(bridgeTestCategory, "the.bridge.test")

}  // namespace

/**
 * @brief Component test of the toolkit messages bridge: the real QtLogBridge
 * over the real Qt logging, with the real application logger behind it, so
 * every case is measured in the log file itself and not in a mock.
 *
 * The bridge is installed once for the whole binary by the own main below,
 * because it takes the single message handler slot of the process once.
 */
class CTEST_QtLogBridge : public Test
{
 public:
  inline static const std::string test_log_file =
      CTEST_QtLogBridge_DATA_DIR "/CTEST_QtLogBridge.log";

  CTEST_QtLogBridge() { clear_log_file(); }
  ~CTEST_QtLogBridge() override { clear_log_file(); }

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
   * @brief Tells whether the toolkit reports the debug messages of the default
   * category at all, which the logging rules of the environment decide. Those
   * rules are read once in the life of a process, so a test can not switch the
   * toolkit chatter on or off for itself.
   */
  static bool toolkit_chatter_switched_on()
  {
    const QLoggingCategory* const defaultCategory =
        QLoggingCategory::defaultCategory();

    return defaultCategory != nullptr && defaultCategory->isDebugEnabled();
  }
};

TEST_F(CTEST_QtLogBridge, warning_reaches_the_log_as_a_warning)
{
  qWarning("a toolkit warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" WRN "));
  EXPECT_THAT(logs, HasSubstr("a toolkit warning of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, critical_reaches_the_log_as_an_error)
{
  // The Qt critical type stands for a broken invariant, the very way it's
  // fatal one does, so both of them are errors of the application log.
  qCritical("a toolkit critical of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" ERR "));
  EXPECT_THAT(logs, HasSubstr("a toolkit critical of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, info_reaches_the_log_as_an_info)
{
  qInfo("a toolkit info of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr(" INF "));
  EXPECT_THAT(logs, HasSubstr("a toolkit info of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, named_category_stands_at_the_front_of_the_message)
{
  qCWarning(bridgeTestCategory, "a categorized warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("the.bridge.test: "));
  EXPECT_THAT(logs, HasSubstr("a categorized warning of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, default_category_is_not_named_in_the_log)
{
  // An uncategorized message of the qWarning and of it's neighbours carries
  // the default category, which is worth no place in the log line - the very
  // way the Qt own default message pattern leaves it out.
  qWarning("an uncategorized warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("an uncategorized warning of the bridge test"));
  EXPECT_THAT(logs, Not(HasSubstr("default: ")));
}

TEST_F(CTEST_QtLogBridge, log_line_names_the_toolkit_source_of_the_message)
{
  // A build of a Qt module which defines the QT_MESSAGELOGCONTEXT names the
  // source file, the line and the function every message came from. The very
  // same fields are given here by hand, because a release build of the toolkit
  // carries none of them - and the bridge keeps all three of them in the
  // message text, with the file name alone of the toolkit path.
  QMessageLogger("/the/toolkit/source/qquickwindow.cpp", 512,
                 "QQuickWindow::event", bridgeTestCategory().categoryName())
      .warning("a located warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("qquickwindow.cpp:512: QQuickWindow::event: "));
  EXPECT_THAT(logs, Not(HasSubstr("/the/toolkit/source/")));
  EXPECT_THAT(logs, HasSubstr("a located warning of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, qml_file_of_a_message_is_named_by_it_is_file_name)
{
  // The QML console calls name their source with an URL of the interface file,
  // and the last element of it is the file name the log line carries.
  QMessageLogger("file:///the/interface/main.qml", 42, "onCompleted", "qml")
      .warning("a QML warning of the bridge test");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("qml: main.qml:42: onCompleted: "));
  EXPECT_THAT(logs, HasSubstr("a QML warning of the bridge test"));
}

TEST_F(CTEST_QtLogBridge, message_keeps_a_single_line_in_the_log)
{
  // A text handed to the toolkit logging by hand may well carry a line ending
  // of a terminal stream, and the logger appends an own one to every message
  // it receives.
  qWarning("a single line of the bridge test\n");

  const std::string logs = log_contents();

  EXPECT_THAT(logs, HasSubstr("a single line of the bridge test"));
  EXPECT_EQ(logs.find("\n\n"), std::string::npos);
}

TEST_F(CTEST_QtLogBridge, debug_message_obeys_the_gate_of_the_build)
{
  if (!toolkit_chatter_switched_on()) {
    GTEST_SKIP() << "The logging rules of the environment drop the toolkit "
                    "debug messages";
  }

  qDebug("a toolkit debug message of the bridge test");

  const std::string logs = log_contents();

#if MAX_LOG_LEVEL >= MACRO_LVL_DEBUG
  EXPECT_THAT(logs, HasSubstr(" DBG "));
  EXPECT_THAT(logs, HasSubstr("a toolkit debug message of the bridge test"));
#else
  // A build which does not keep it's own debug messages drops the toolkit ones
  // as well, whatever the logging rules of the toolkit say.
  EXPECT_THAT(logs,
              Not(HasSubstr("a toolkit debug message of the bridge test")));
#endif  // MAX_LOG_LEVEL
}

TEST_F(CTEST_QtLogBridge, repeated_install_is_ignored)
{
  QtLogBridge::install();
  QtLogBridge::install();

  qWarning("a warning after the repeated install");

  EXPECT_THAT(log_contents(),
              HasSubstr("a warning after the repeated install"));
}

int main(int argc, char** argv)
{
  // The application has it's logger ready before the toolkit is touched, and
  // the Qt logging is taken over right after that, exactly the way the
  // Qt6Initer does it. Both happen once for the whole binary, because the
  // bridge takes the single message handler slot of the process once.
  LOG_INIT(CTEST_QtLogBridge::test_log_file, MACRO_LVL_TRACE, false);

  QtLogBridge::install();

  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
