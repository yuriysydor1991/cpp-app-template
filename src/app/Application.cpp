#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/qt6/Qt6Initer.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  std::shared_ptr<templateQt6app::Qt6Initer> qt6runner = create_qt6_initer();

  return qt6runner->run(ctx->argc, ctx->argv);
}

std::shared_ptr<templateQt6app::Qt6Initer> Application::create_qt6_initer()
{
  return std::make_shared<templateQt6app::Qt6Initer>();
}

}  // namespace app
