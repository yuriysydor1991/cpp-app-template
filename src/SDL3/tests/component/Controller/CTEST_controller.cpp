#include <SDL3/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL3/SDL3Controller.h"
#include "src/app/ApplicationContext.h"
#include "src/app/applications/IApplication.h"

using namespace app;
using namespace templateSDL3;
using namespace testing;

class CTEST_controller : public Test
{
 public:
  CTEST_controller() : appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
  SDL3Controller controller;
};

TEST_F(CTEST_controller, run_fails_without_context)
{
  EXPECT_EQ(controller.run({}), IApplication::INVALID);
}

TEST_F(CTEST_controller, run_fails_without_any_video_device)
{
  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "nonexistent",
                          SDL_HINT_OVERRIDE);

  EXPECT_EQ(controller.run(appCtx), IApplication::INVALID);
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(CTEST_controller, run_fails_without_an_opengl_window)
{
  // the dummy video driver creates no OpenGL windows
  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "dummy", SDL_HINT_OVERRIDE);

  EXPECT_EQ(controller.run(appCtx), IApplication::INVALID);
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(CTEST_controller, run_returns_on_the_raised_stop_flag)
{
  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "offscreen",
                          SDL_HINT_OVERRIDE);

  appCtx->set_stop(true);

  if (controller.run(appCtx) != 0) {
    GTEST_SKIP() << "No offscreen OpenGL 3.3 core context available";
  }

  EXPECT_TRUE(appCtx->get_stop());
}
