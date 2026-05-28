#include "src/SFML/SFMLIniter.h"

#include <cassert>
#include <memory>
#include <stdexcept>

#include "src/SFML/SFMLContext.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace templateSFML
{

SFMLIniter::SFMLIniter()
    : ctxBuilder{std::make_shared<SFMLContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter2d{std::make_shared<painter::Painter>()}
{
}

SFMLIniter::~SFMLIniter() { sfmlContext.reset(); }

int SFMLIniter::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return app::IApplication::INVALID;
  }

  sfmlContext = ctxBuilder->build_context(ctx);

  assert(sfmlContext != nullptr);

  if (sfmlContext == nullptr) {
    LOGE("Fail to create the SFML context");
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SFMLIniter::event_loop()
{
  assert(sfmlContext != nullptr);
  assert(sfmlContext->appCtx != nullptr);
  assert(sfmlContext->window != nullptr);
  assert(events != nullptr);
  assert(painter2d != nullptr);

  if (sfmlContext == nullptr || sfmlContext->window == nullptr) {
    throw std::runtime_error("No valid SFML context given");
  }

  if (painter2d == nullptr) {
    throw std::runtime_error("No scene painter given");
  }

  if (events == nullptr) {
    throw std::runtime_error("No event handler given");
  }

  while (!sfmlContext->appCtx->stop() && sfmlContext->window->isOpen()) {
    events->handle(sfmlContext);

    painter2d->paint(sfmlContext);

    sfmlContext->window->display();
  }
}

}  // namespace templateSFML
