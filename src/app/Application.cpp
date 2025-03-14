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

  auto qt6runner = std::make_shared<templateQt6app::Qt6Initer>();

  return qt6runner->run(ctx->argc, ctx->argv);
}

}  // namespace app
