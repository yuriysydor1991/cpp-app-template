#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/SFML/SFMLIniter.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  templateSFML::SFMLIniter sfml;

  if (sfml.run(ctx) != 0) {
    LOGE("The SFML controller returned invalid state");
    return INVALID;
  }

  return 0;
}

}  // namespace app
