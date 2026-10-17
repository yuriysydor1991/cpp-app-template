#include <SDL2/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL2/Eventer/EventsHandlers/EventWindowResizedHandler.h"
#include "src/SDL2/SDL2Context.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL2;
using namespace templateSDL2::events::eventsHandlers;
using namespace testing;

class UTEST_EventWindowResizedHandler : public Test
{
 public:
  UTEST_EventWindowResizedHandler()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sdlCtx{std::make_shared<SDL2Context>(appCtx)},
        handler{std::make_shared<EventWindowResizedHandler>()}
  {
    resizeEvent.type = SDL_WINDOWEVENT;
    resizeEvent.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
    resizeEvent.window.data1 = 320;
    resizeEvent.window.data2 = 200;
  }

  int argc{0};
  char** argv{nullptr};

  SDL_Event resizeEvent{};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SDL2Context> sdlCtx;
  std::shared_ptr<EventWindowResizedHandler> handler;
};

TEST_F(UTEST_EventWindowResizedHandler, resize_event_is_handled)
{
  EXPECT_TRUE(handler->handle(resizeEvent, sdlCtx));
}

TEST_F(UTEST_EventWindowResizedHandler, resize_event_keeps_running)
{
  EXPECT_TRUE(handler->handle(resizeEvent, sdlCtx));

  EXPECT_FALSE(appCtx->get_stop());
}
