#include <SDL2/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL2/Eventer/EventsHandlers/EventQuitHandler.h"
#include "src/SDL2/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL2/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SDL2/SDL2Context.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL2;
using namespace templateSDL2::events;
using namespace templateSDL2::events::eventsHandlers;
using namespace testing;

class CTEST_eventer : public Test
{
 public:
  CTEST_eventer()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sdlCtx{std::make_shared<SDL2Context>(appCtx)},
        factory{std::make_shared<EventsHandlersFactory>()}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SDL2Context> sdlCtx;
  std::shared_ptr<EventsHandlersFactory> factory;
};

TEST_F(CTEST_eventer, quit_event_routed_to_quit_handler_stops_loop)
{
  SDL_Event event{};
  event.type = SDL_QUIT;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

  EXPECT_NE(handler, nullptr);

  EXPECT_FALSE(appCtx->stop());

  EXPECT_TRUE(handler->handle(event, sdlCtx));

  EXPECT_TRUE(appCtx->stop());
}

TEST_F(CTEST_eventer, unhandled_event_does_not_alter_stop_flag)
{
  SDL_Event event{};
  event.type = 0xFFFFFFFFU;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

  EXPECT_EQ(handler, nullptr);
  EXPECT_FALSE(appCtx->stop());
}

TEST_F(CTEST_eventer, multiple_quit_events_keep_stop_flag_set)
{
  SDL_Event event{};
  event.type = SDL_QUIT;

  for (int i = 0; i < 3; ++i) {
    std::shared_ptr<IEventHandler> handler = factory->create(event, sdlCtx);

    EXPECT_NE(handler, nullptr);
    EXPECT_TRUE(handler->handle(event, sdlCtx));
  }

  EXPECT_TRUE(appCtx->stop());
}
