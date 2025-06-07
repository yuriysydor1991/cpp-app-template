#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/qt6/Qt6Initer.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<Qt6i::Qt6Initer> qt6runner = create_qt6_initer();

  assert(qt6runner != nullptr);

  if (qt6runner->run(ctx) != 0) {
    LOGE("Qt6 controller returned invalid status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<Qt6i::Qt6Initer> Application::create_qt6_initer()
{
  return std::make_shared<Qt6i::Qt6Initer>();
}

}  // namespace app
