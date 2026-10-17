#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>

#include "src/SFML/SFMLController.h"
#include "src/app/ApplicationContext.h"
#include "src/app/applications/IApplication.h"

using namespace app;
using namespace templateSFML;
using namespace testing;

class CTEST_controller : public Test
{
 public:
  CTEST_controller() : appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  // the SFML window creation aborts the process without an X display
  static bool has_display()
  {
    const char* display = std::getenv("DISPLAY");

    return display != nullptr && *display != '\0';
  }

  char arg0[17]{"CTEST_controller"};
  char* args[2]{arg0, nullptr};

  int argc{1};
  char** argv{args};

  std::shared_ptr<ApplicationContext> appCtx;
  SFMLController controller;
};

TEST_F(CTEST_controller, run_fails_without_context)
{
  EXPECT_EQ(controller.run({}), IApplication::INVALID);
}

TEST_F(CTEST_controller, run_returns_on_the_raised_stop_flag)
{
  if (!has_display()) {
    GTEST_SKIP() << "No X display for the SFML window";
  }

  appCtx->set_stop(true);

  EXPECT_EQ(controller.run(appCtx), 0);
}

TEST_F(CTEST_controller, run_returns_when_the_stop_flag_is_raised_later)
{
  if (!has_display()) {
    GTEST_SKIP() << "No X display for the SFML window";
  }

  std::thread stopper{[this]() {
    std::this_thread::sleep_for(std::chrono::milliseconds{300});
    appCtx->set_stop(true);
  }};

  const auto start = std::chrono::steady_clock::now();

  EXPECT_EQ(controller.run(appCtx), 0);

  stopper.join();

  EXPECT_LT(std::chrono::steady_clock::now() - start, std::chrono::seconds{5});
}
