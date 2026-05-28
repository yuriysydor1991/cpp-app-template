#include <SFML/Window/Event.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/EventClosedHandler.h"
#include "src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSFML;
using namespace templateSFML::events::eventsHandlers;
using namespace testing;

class UTEST_EventsHandlersFactory : public Test
{
 public:
  UTEST_EventsHandlersFactory()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sfmlCtx{std::make_shared<SFMLContext>(appCtx)},
        factory{std::make_shared<EventsHandlersFactory>()}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SFMLContext> sfmlCtx;
  std::shared_ptr<EventsHandlersFactory> factory;
};

TEST_F(UTEST_EventsHandlersFactory, closed_event_returns_closed_handler)
{
  sf::Event event{};
  event.type = sf::Event::Closed;

  auto handler = factory->create(event, sfmlCtx);

  EXPECT_NE(handler, nullptr);

  auto casted = std::dynamic_pointer_cast<EventClosedHandler>(handler);

  EXPECT_NE(casted, nullptr);
}

TEST_F(UTEST_EventsHandlersFactory, unknown_event_returns_null)
{
  sf::Event event{};
  event.type = sf::Event::GainedFocus;

  auto handler = factory->create(event, sfmlCtx);

  EXPECT_EQ(handler, nullptr);
}

TEST_F(UTEST_EventsHandlersFactory, repeated_create_calls_return_fresh_instances)
{
  sf::Event event{};
  event.type = sf::Event::Closed;

  auto first = factory->create(event, sfmlCtx);
  auto second = factory->create(event, sfmlCtx);

  EXPECT_NE(first, nullptr);
  EXPECT_NE(second, nullptr);
  EXPECT_NE(first, second);
}
