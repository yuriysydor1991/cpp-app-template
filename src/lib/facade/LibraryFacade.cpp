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
auto libFactory = std::make_shared<lib0impl::LibFactory>();
}  // namespace

std::shared_ptr<LibraryContext> LibraryFacade::create_library_context()
{
  assert(libFactory != nullptr);

  if (libFactory == nullptr) {
    return {};
  }

  return libFactory->create_default_context();
}

bool LibraryFacade::libcall(
    [[maybe_unused]] std::shared_ptr<LibraryContext> ctx)
{
  assert(ctx != nullptr);
  assert(libFactory != nullptr);

  if (libFactory == nullptr) {
    return false;
  }

  auto libInstance = libFactory->create_appropriate_lib(ctx);

  assert(libInstance != nullptr);

  if (libInstance == nullptr) {
    return false;
  }

  return libInstance->libcall(ctx);
}

}  // namespace templatelib
