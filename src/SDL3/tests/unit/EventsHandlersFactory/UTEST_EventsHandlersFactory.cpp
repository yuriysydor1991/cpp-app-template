#include <SDL3/SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/EventQuitHandler.h"
#include "src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL3/SDL3Context.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL3;
using namespace templateSDL3::events::eventsHandlers;
using namespace testing;

class UTEST_EventsHandlersFactory : public Test
{
 public:
  UTEST_EventsHandlersFactory()
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

TEST_F(UTEST_EventsHandlersFactory, quit_event_returns_quit_handler)
{
  SDL_Event event{};
  event.type = SDL_EVENT_QUIT;

  auto handler = factory->create(event, sdlCtx);

  EXPECT_NE(handler, nullptr);

  auto casted = std::dynamic_pointer_cast<EventQuitHandler>(handler);

  EXPECT_NE(casted, nullptr);
}

TEST_F(UTEST_EventsHandlersFactory, unknown_event_returns_null)
{
  SDL_Event event{};
  event.type = 0xFFFFFFFFU;

  auto handler = factory->create(event, sdlCtx);

  EXPECT_EQ(handler, nullptr);
}

TEST_F(UTEST_EventsHandlersFactory, repeated_create_calls_return_fresh_instances)
{
  SDL_Event event{};
  event.type = SDL_EVENT_QUIT;

  auto first = factory->create(event, sdlCtx);
  auto second = factory->create(event, sdlCtx);

  EXPECT_NE(first, nullptr);
  EXPECT_NE(second, nullptr);
  EXPECT_NE(first, second);
}
