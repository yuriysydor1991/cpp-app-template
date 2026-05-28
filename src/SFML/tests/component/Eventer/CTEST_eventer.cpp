#include <SFML/Window/Event.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/EventClosedHandler.h"
#include "src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SFML/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSFML;
using namespace templateSFML::events;
using namespace templateSFML::events::eventsHandlers;
using namespace testing;

/**
 * @brief Component test for the SFML event subsystem. It drives the real
 * EventsHandlersFactory and the produced handler end to end and asserts the
 * window-closed event ultimately stops the application event loop. No on-screen
 * window is ever opened, so it stays usable on a headless CI agent.
 */
class CTEST_eventer : public Test
{
 public:
  CTEST_eventer()
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

TEST_F(CTEST_eventer, closed_event_routed_to_closed_handler_stops_loop)
{
  sf::Event event{};
  event.type = sf::Event::Closed;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sfmlCtx);

  EXPECT_NE(handler, nullptr);

  EXPECT_FALSE(appCtx->stop());

  EXPECT_TRUE(handler->handle(event, sfmlCtx));

  EXPECT_TRUE(appCtx->stop());
}

TEST_F(CTEST_eventer, unhandled_event_does_not_alter_stop_flag)
{
  sf::Event event{};
  event.type = sf::Event::GainedFocus;

  std::shared_ptr<IEventHandler> handler = factory->create(event, sfmlCtx);

  EXPECT_EQ(handler, nullptr);
  EXPECT_FALSE(appCtx->stop());
}

TEST_F(CTEST_eventer, multiple_closed_events_keep_stop_flag_set)
{
  sf::Event event{};
  event.type = sf::Event::Closed;

  for (int i = 0; i < 3; ++i) {
    std::shared_ptr<IEventHandler> handler = factory->create(event, sfmlCtx);

    EXPECT_NE(handler, nullptr);
    EXPECT_TRUE(handler->handle(event, sfmlCtx));
  }

  EXPECT_TRUE(appCtx->stop());
}
