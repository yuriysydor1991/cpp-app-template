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

  std::shared_ptr<templatelib0::LibraryFacade> libfacade =
      create_lib_instance();

  assert(libfacade != nullptr);

  if (libfacade == nullptr) {
    LOGE("No library instance created");
    ctx->push_error("No library instance created");
    return INVALID;
  }

  auto libctx = create_and_convert_libctx(libfacade, ctx);

  assert(libctx != nullptr);

  if (libctx == nullptr) {
    LOGE("Fail to create the library context");
    return INVALID;
  }

  if (!libfacade->libcall(libctx)) {
    LOGE("Invalid library execution status");
    ctx->push_error("Invalid library execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<templatelib0::LibraryContext>
Application::create_and_convert_libctx(
    std::shared_ptr<templatelib0::LibraryFacade> libfacade,
    std::shared_ptr<ApplicationContext> ctx)
{
  std::shared_ptr<templatelib0::LibraryContext> libctx =
      libfacade->create_library_context();

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

std::shared_ptr<templatelib0::LibraryFacade> Application::create_lib_instance()
{
  return std::make_shared<templatelib0::LibraryFacade>();
}

std::shared_ptr<converters::ApplicationContext2LibraryContext>
Application::create_ctx_converter()
{
  return std::make_shared<converters::ApplicationContext2LibraryContext>();
}

}  // namespace app
