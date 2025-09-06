#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "LibraryContext.h"
#include "LibraryFacade.h"
#include "src/converters/ApplicationContext2LibraryContext.h"
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

  auto libctx = create_and_convert_libctx(ctx);

  assert(libctx != nullptr);

  if (libctx == nullptr) {
    LOGE("Fail to create the library context");
    return INVALID;
  }

  auto libi = templatelib0::LibraryFacade::create_library(libctx);

  if (!libi->libcall(libctx)) {
    LOGE("Invalid library execution status");
    ctx->push_error("Invalid library execution status");
    return INVALID;
  }

  return 0;
}

Application::LibraryContextPtr Application::create_and_convert_libctx(
    std::shared_ptr<ApplicationContext> ctx)
{
  LibraryContextPtr libctx =
      templatelib0::LibraryFacade::create_library_context();

  assert(libctx != nullptr);

  if (libctx == nullptr) {
    LOGE("No library context instance was created");
    ctx->push_error("No library context instance was created");
    return {};
  }

  auto converter = create_ctx_converter();

  assert(converter != nullptr);

  if (converter == nullptr) {
    LOGE("No context converter instance was created");
    ctx->push_error("No context converter instance was created");
    return {};
  }

  if (!converter->convert(ctx, libctx)) {
    LOGE("Failure during context conversion");
    ctx->push_error("Failure during context conversion");
    return {};
  }

  return libctx;
}

Application::DefaultCtxConPtr Application::create_ctx_converter()
{
  return std::make_shared<converters::ApplicationContext2LibraryContext>();
}

}  // namespace app
