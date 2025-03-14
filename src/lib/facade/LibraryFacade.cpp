#include "src/lib/facade/LibraryFacade.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/lib/libmain/LibFactory.h"

namespace templatelib0
{

namespace
{
/// @brief The LibraryFacade class internal fields should be placed
/// here to avoid installable LibraryFacade.h file to have visible
/// library internals.
auto libFactory = lib0impl::LibFactory::create_factory();
}  // namespace

std::shared_ptr<LibraryContext> LibraryFacade::create_library_context()
{
  assert(libFactory != nullptr);

  if (libFactory == nullptr) {
    return {};
  }

  return libFactory->create_default_context();
}

std::shared_ptr<ILib> LibraryFacade::create_library(
    std::shared_ptr<LibraryContext> ctx)
{
  assert(libFactory != nullptr);

  if (libFactory == nullptr) {
    return {};
  }

  return libFactory->create_appropriate_lib(ctx);
}

bool LibraryFacade::libcall(std::shared_ptr<LibraryContext> ctx)
{
  assert(ctx != nullptr);
  assert(libFactory != nullptr);

  if (libFactory == nullptr) {
    return false;
  }

  if (ctx == nullptr) {
    return false;
  }

  auto libInstance = create_library(ctx);

  assert(libInstance != nullptr);

  if (libInstance == nullptr) {
    return false;
  }

  return libInstance->libcall(ctx);
}

}  // namespace templatelib0
