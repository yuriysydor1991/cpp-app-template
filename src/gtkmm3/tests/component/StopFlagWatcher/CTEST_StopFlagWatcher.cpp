#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm3/StopFlagWatcher.h"

using namespace app;
using namespace testing;
using namespace Gtkmm3i;

/**
 * @brief Runs a real GIO application main loop, which the watcher has to quit
 * once the stop flag is raised. A safety timer quits the loop on it's own
 * after a while, so a broken watcher fails the case instead of hanging it.
 */
class CTEST_StopFlagWatcher : public Test
{
 public:
  CTEST_StopFlagWatcher()
  {
    Gio::init();

    gapp = Gio::Application::create("ua.org.kytok.template.CTEST",
                                    Gio::APPLICATION_NON_UNIQUE);

    gapp->signal_activate().connect([this]() { gapp->hold(); });
  }

  /// @brief Runs the main loop and tells whether the safety timer quit it.
  bool run_timed_out()
  {
    bool timedOut{false};

    auto safety = Glib::signal_timeout().connect(
        [this, &timedOut]() {
          timedOut = true;
          gapp->quit();
          return false;
        },
        safety_timeout_ms);

    EXPECT_EQ(gapp->run(0, nullptr), 0);

    safety.disconnect();

    return timedOut;
  }

  inline static constexpr unsigned int safety_timeout_ms = 3000;

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};

  Glib::RefPtr<Gio::Application> gapp;
};

TEST_F(CTEST_StopFlagWatcher, raised_stop_flag_quits_the_main_loop)
{
  const StopFlagWatcher watcher{ctx, *gapp.get()};

  Glib::signal_timeout().connect_once([this]() { ctx->set_stop(true); }, 200);

  EXPECT_FALSE(run_timed_out());
}

TEST_F(CTEST_StopFlagWatcher, lowered_stop_flag_keeps_the_main_loop_running)
{
  const StopFlagWatcher watcher{ctx, *gapp.get()};

  EXPECT_TRUE(run_timed_out());
}

TEST_F(CTEST_StopFlagWatcher, destroyed_watcher_stops_polling_the_flag)
{
  {
    const StopFlagWatcher watcher{ctx, *gapp.get()};
  }

  ctx->set_stop(true);

  EXPECT_TRUE(run_timed_out());
}
