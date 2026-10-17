#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/app/StopFlagWatcher.h"
#include "src/wxwidgets/wxwidgets_includes.h"

using namespace testing;

namespace
{

/**
 * @brief A console wxWidgets application, which runs a real main loop with
 * the watcher in it. A safety timer leaves the loop on it's own after a while,
 * so a broken watcher fails the case instead of hanging it.
 */
class WatchedApp : public wxAppConsole
{
 public:
  WatchedApp(std::shared_ptr<app::ApplicationContext> nctx, bool nraise,
             bool& ntimedOut)
      : ctx{std::move(nctx)}, raise{nraise}, timedOut{ntimedOut}
  {
  }

  bool OnInit() override
  {
    watcher = std::make_unique<wxwi::app::StopFlagWatcher>(ctx);
    watcher->Start(wxwi::app::StopFlagWatcher::poll_period_ms);

    // The timers belong to the initialized application, so they are created
    // here and not by the constructor.
    safety = std::make_unique<wxTimer>(this, safetyId);
    Bind(wxEVT_TIMER, &WatchedApp::on_safety_timeout, this, safetyId);
    safety->StartOnce(safety_timeout_ms);

    if (raise) {
      raiser = std::make_unique<wxTimer>(this, raiseId);
      Bind(wxEVT_TIMER, &WatchedApp::on_raise, this, raiseId);
      raiser->StartOnce(raise_after_ms);
    }

    return true;
  }

  int OnExit() override
  {
    watcher.reset();
    safety.reset();
    raiser.reset();

    return wxAppConsole::OnExit();
  }

  inline static constexpr int safety_timeout_ms = 3000;
  inline static constexpr int raise_after_ms = 200;
  inline static constexpr int safetyId = 1;
  inline static constexpr int raiseId = 2;

 private:
  void on_safety_timeout(wxTimerEvent& /*event*/)
  {
    timedOut = true;
    ExitMainLoop();
  }

  void on_raise(wxTimerEvent& /*event*/) { ctx->set_stop(true); }

  std::shared_ptr<app::ApplicationContext> ctx;
  bool raise;
  bool& timedOut;

  std::unique_ptr<wxwi::app::StopFlagWatcher> watcher;
  std::unique_ptr<wxTimer> safety;
  std::unique_ptr<wxTimer> raiser;
};

}  // namespace

class CTEST_WxStopFlagWatcher : public Test
{
 public:
  /// @brief Runs the watched main loop and tells whether the safety timer
  /// left it.
  bool run_timed_out(const bool raise)
  {
    bool timedOut{false};

    // wxEntry() deletes the application object on it's cleanup.
    wxApp::SetInstance(new WatchedApp{ctx, raise, timedOut});

    int wxArgc{1};
    char program[] = "CTEST_WxStopFlagWatcher";
    char* wxArgvItems[] = {program, nullptr};
    char** wxArgv = wxArgvItems;

    EXPECT_EQ(wxEntry(wxArgc, wxArgv), 0);

    return timedOut;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> ctx{
      std::make_shared<app::ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_WxStopFlagWatcher, raised_stop_flag_leaves_the_main_loop)
{
  EXPECT_FALSE(run_timed_out(true));
}

TEST_F(CTEST_WxStopFlagWatcher, lowered_stop_flag_keeps_the_main_loop_running)
{
  EXPECT_TRUE(run_timed_out(false));
}
