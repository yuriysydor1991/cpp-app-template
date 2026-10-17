#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <fstream>
#include <memory>
#include <string>
#include <thread>

#include "src/app/ApplicationContext.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"
#include "src/qt6/Qt6Controller.h"

using namespace testing;
using namespace Qt6i;

/**
 * @brief Component test of the Qt6Controller: the real QML modules of the
 * project are loaded on the offscreen platform (the ctest environment sets
 * the QT_QPA_PLATFORM) and the event loop is left on the raised stop flag of
 * a real application context, the very way the OS signals handlers raise it.
 */
class CTEST_Qt6Controller : public Test
{
 public:
  inline static const std::string test_log_file =
      CTEST_Qt6Controller_DATA_DIR "/CTEST_Qt6Controller.log";

  void SetUp() override
  {
    std::fstream{test_log_file.c_str(),
                 std::fstream::out | std::fstream::trunc};
    LOG_INIT(test_log_file, MACRO_LVL_TRACE, false);
  }

  std::string log_contents()
  {
    // Reopening the log file flushes the messages below the warning level.
    LOG_INIT(test_log_file, MACRO_LVL_TRACE, false);

    std::ifstream log{test_log_file};

    return {std::istreambuf_iterator<char>{log},
            std::istreambuf_iterator<char>{}};
  }

  char arg0[20]{"CTEST_Qt6Controller"};
  char* args[2]{arg0, nullptr};
  int argc{1};
  char** argv{args};

  std::shared_ptr<app::ApplicationContext> ctx{
      std::make_shared<app::ApplicationContext>(argc, argv)};

  Qt6Controller controller;
};

TEST_F(CTEST_Qt6Controller, raised_stop_flag_leaves_the_event_loop)
{
  std::thread signal{[this]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx->set_stop(true);
  }};

  EXPECT_EQ(controller.run(ctx), 0);

  signal.join();

  EXPECT_THAT(log_contents(), HasSubstr("leaving the Qt event loop"));
}

TEST_F(CTEST_Qt6Controller, main_window_finds_every_resource)
{
  ctx->set_stop(true);

  EXPECT_EQ(controller.run(ctx), 0);

  const std::string logs = log_contents();

  EXPECT_THAT(logs, Not(HasSubstr("Cannot open")));
  EXPECT_THAT(logs, Not(HasSubstr("is not a type")));
  // The map draws nothing without the osm geo services plugin.
  EXPECT_THAT(logs, Not(HasSubstr("NotSupportedError")));
}
