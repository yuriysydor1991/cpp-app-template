#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/gtkmm3/GtkmmIniter.h"
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

  std::shared_ptr<templateGtkmm3::GtkmmIniter> gtkmmIniter =
      create_gtkmm_initer();

  if (gtkmmIniter->run(ctx) != 0) {
    LOGE("The gtkmm controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<templateGtkmm3::GtkmmIniter> Application::create_gtkmm_initer()
{
  return std::make_shared<templateGtkmm3::GtkmmIniter>();
}

}  // namespace app
