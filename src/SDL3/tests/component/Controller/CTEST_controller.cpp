#include <SDL3/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL3/OpenGLIniter.h"
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

TEST_F(CTEST_controller, opengl_attributes_fail_before_the_video_init)
{
  OpenGLIniter initer;

  EXPECT_FALSE(initer.init_opengl());
}

TEST_F(CTEST_controller, opengl_attributes_request_the_core_profile)
{
  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "dummy", SDL_HINT_OVERRIDE);

  ASSERT_TRUE(SDL_InitSubSystem(SDL_INIT_VIDEO));

  OpenGLIniter initer;

  EXPECT_TRUE(initer.init_opengl());

  int major{0};
  int minor{0};
  int profile{0};

  EXPECT_TRUE(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major));
  EXPECT_TRUE(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor));
  EXPECT_TRUE(SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile));

  EXPECT_EQ(major, 3);
  EXPECT_EQ(minor, 3);
  EXPECT_EQ(profile, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
