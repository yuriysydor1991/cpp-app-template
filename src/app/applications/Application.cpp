#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/gtkmm3/Gtkmm3Controller.h"
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

  std::shared_ptr<Gtkmm3i::Gtkmm3Controller> gtkmmController =
      create_gtkmm_controller();

  if (gtkmmController->run(ctx) != 0) {
    LOGE("The gtkmm controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<Gtkmm3i::Gtkmm3Controller>
Application::create_gtkmm_controller()
{
  return std::make_shared<Gtkmm3i::Gtkmm3Controller>();
}

}  // namespace app
