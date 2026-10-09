#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/gettext/tr.h"
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

  // Insert your translated messages here. The ApplicationFactory binds the
  // catalogs of the po directory before the run, so the gettexti::tr call
  // gives the message in the language of the user.
  std::cout << gettexti::tr(
                   "Hello, gettext! Insert your translated messages here!")
            << std::endl;

  return 0;
}

}  // namespace app
