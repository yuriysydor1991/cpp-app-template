#include <SFML/Window/Event.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/EventClosedHandler.h"
#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSFML;
using namespace templateSFML::events::eventsHandlers;
using namespace testing;

class UTEST_EventClosedHandler : public Test
{
 public:
  UTEST_EventClosedHandler()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        sfmlCtx{std::make_shared<SFMLContext>(appCtx)},
        handler{std::make_shared<EventClosedHandler>()}
  {
    closedEvent.type = sf::Event::Closed;
  }

  int argc{0};
  char** argv{nullptr};

  sf::Event closedEvent{};

  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<SFMLContext> sfmlCtx;
  std::shared_ptr<EventClosedHandler> handler;
};

TEST_F(UTEST_EventClosedHandler, closed_event_sets_stop_flag)
{
  EXPECT_FALSE(appCtx->stop());

  EXPECT_TRUE(handler->handle(closedEvent, sfmlCtx));

  EXPECT_TRUE(appCtx->stop());
}

TEST_F(UTEST_EventClosedHandler, null_sfml_context_returns_false)
{
  EXPECT_FALSE(handler->handle(closedEvent, {}));
}

TEST_F(UTEST_EventClosedHandler, null_app_context_returns_false)
{
  auto brokenSfmlCtx = std::make_shared<SFMLContext>(appCtx);

  brokenSfmlCtx->appCtx.reset();

  EXPECT_FALSE(handler->handle(closedEvent, brokenSfmlCtx));
}

TEST_F(UTEST_EventClosedHandler, repeated_handle_keeps_stop_flag_set)
{
  EXPECT_TRUE(handler->handle(closedEvent, sfmlCtx));
  EXPECT_TRUE(appCtx->stop());

  EXPECT_TRUE(handler->handle(closedEvent, sfmlCtx));
  EXPECT_TRUE(appCtx->stop());
}
