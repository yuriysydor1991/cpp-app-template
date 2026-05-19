#include <SDL2/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL2/Eventer/EventsHandlers/EventQuitHandler.h"
#include "src/SDL2/SDL2Context.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL2;
using namespace templateSDL2::events::eventsHandlers;
using namespace testing;

class UTEST_EventQuitHandler : public Test
{
 public:
  UTEST_EventQuitHandler()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sdlCtx{std::make_shared<SDL2Context>(appCtx)},
        handler{std::make_shared<EventQuitHandler>()}
  {
    quitEvent.type = SDL_QUIT;
  }

  int argc{0};
  char** argv{nullptr};

  SDL_Event quitEvent{};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SDL2Context> sdlCtx;
  std::shared_ptr<EventQuitHandler> handler;
};

TEST_F(UTEST_EventQuitHandler, quit_event_sets_stop_flag)
{
  EXPECT_FALSE(appCtx->stop());

  EXPECT_TRUE(handler->handle(quitEvent, sdlCtx));

  EXPECT_TRUE(appCtx->stop());
}

TEST_F(UTEST_EventQuitHandler, null_sdl_context_returns_false)
{
  EXPECT_FALSE(handler->handle(quitEvent, {}));
}

TEST_F(UTEST_EventQuitHandler, null_app_context_returns_false)
{
  auto brokenSdlCtx = std::make_shared<SDL2Context>(appCtx);

  brokenSdlCtx->appCtx.reset();

  EXPECT_FALSE(handler->handle(quitEvent, brokenSdlCtx));
}

TEST_F(UTEST_EventQuitHandler, repeated_handle_keeps_stop_flag_set)
{
  EXPECT_TRUE(handler->handle(quitEvent, sdlCtx));
  EXPECT_TRUE(appCtx->stop());

  EXPECT_TRUE(handler->handle(quitEvent, sdlCtx));
  EXPECT_TRUE(appCtx->stop());
}
