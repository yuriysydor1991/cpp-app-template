#include "src/SFML/SFMLContext.h"

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSFML
{

SFMLContext::~SFMLContext()
{
  if (window != nullptr && window->isOpen()) {
    window->close();
  }
}

SFMLContext::SFMLContext(std::shared_ptr<app::ApplicationContext> ctx)
    : appCtx{ctx}
{
  assert(appCtx != nullptr);
}

}  // namespace templateSFML
