#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/EventQuitHandler.h"
#include "src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL3/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SDL3/OpenGLIniter.h"
#include "src/SDL3/SDL3Context.h"
#include "src/SDL3/SDL3ContextBuilder.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL3;
using namespace templateSDL3::events;
using namespace templateSDL3::events::eventsHandlers;
using namespace testing;

class CTEST_eventer : public Test
{
 public:
  CTEST_eventer()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sdlCtx{std::make_shared<SDL3Context>(appCtx)},
        factory{std::make_shared<EventsHandlersFactory>()}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SDL3Context> sdlCtx;
  std::shared_ptr<EventsHandlersFactory> factory;
};

TEST_F(CTEST_eventer, quit_event_routed_to_quit_handler_stops_loop)
{
  SDL_Event event{};
  event.type = SDL_EVENT_QUIT;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

  EXPECT_NE(handler, nullptr);

  EXPECT_FALSE(appCtx->get_stop());

  EXPECT_TRUE(handler->handle(event, sdlCtx));

  EXPECT_TRUE(appCtx->get_stop());
}

TEST_F(CTEST_eventer, unhandled_event_does_not_alter_stop_flag)
{
  SDL_Event event{};
  event.type = 0xFFFFFFFFU;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

  EXPECT_EQ(handler, nullptr);
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(CTEST_eventer, multiple_quit_events_keep_stop_flag_set)
{
  SDL_Event event{};
  event.type = SDL_EVENT_QUIT;

  for (int i = 0; i < 3; ++i) {
    std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

    EXPECT_NE(handler, nullptr);
    EXPECT_TRUE(handler->handle(event, sdlCtx));
  }

  EXPECT_TRUE(appCtx->get_stop());
}

TEST_F(CTEST_eventer, resize_event_updates_the_opengl_viewport)
{
  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "offscreen",
                          SDL_HINT_OVERRIDE);

  ASSERT_TRUE(SDL_Init(SDL_INIT_VIDEO));

  OpenGLIniter initer;
  SDL3ContextBuilder builder;

  std::shared_ptr<SDL3Context> glCtx =
      initer.init_opengl() ? builder.build_context(appCtx) : nullptr;

  if (glCtx == nullptr) {
    SDL_Quit();
    GTEST_SKIP() << "No offscreen OpenGL 3.3 core context available";
  }

  SDL_Event event{};
  event.type = SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED;
  event.window.data1 = 320;
  event.window.data2 = 200;

  std::shared_ptr<IEventHandler> handler = factory->create(event, glCtx);

  ASSERT_NE(handler, nullptr);
  EXPECT_TRUE(handler->handle(event, glCtx));

  GLint viewport[4]{};
  glGetIntegerv(GL_VIEWPORT, viewport);

  EXPECT_EQ(viewport[2], 320);
  EXPECT_EQ(viewport[3], 200);
  EXPECT_FALSE(appCtx->get_stop());

  glCtx.reset();
  SDL_Quit();
}
