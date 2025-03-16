#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/gtkmm3/GtkmmIniter.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  std::shared_ptr<templateGtkmm3::GtkmmIniter> gtkmmIniter =
      create_gtkmm_initer();

  return gtkmmIniter->run(ctx->argc, ctx->argv);
}

std::shared_ptr<templateGtkmm3::GtkmmIniter> Application::create_gtkmm_initer()
{
  return std::make_shared<templateGtkmm3::GtkmmIniter>();
}

}  // namespace app
