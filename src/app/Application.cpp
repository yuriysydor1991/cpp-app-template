#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "LibraryContext.h"
#include "LibraryFacade.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  std::shared_ptr<templatelib::LibraryFacade> libfacade = create_lib_instance();

  assert(libfacade != nullptr);

  if (libfacade == nullptr) {
    ctx->push_error("No library instance created");
    return INVALID;
  }

  std::shared_ptr<templatelib::LibraryContext> libctx =
      libfacade->create_library_context();

  assert(libctx != nullptr);

  if (libctx == nullptr) {
    ctx->push_error("No library context instance was created");
    return INVALID;
  }

  if (!libfacade->libcall(libctx)) {
    return INVALID;
  }

  return 0;
}

std::shared_ptr<templatelib::LibraryFacade> Application::create_lib_instance()
{
  return std::make_shared<templatelib::LibraryFacade>();
}

}  // namespace app
