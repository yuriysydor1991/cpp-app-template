#include "LibraryFacade.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/lib/libmain/LibFactory.h"

namespace templatelib0
{

LibraryContextPtr LibraryFacade::create_library_context()
{
  auto libFactory = lib0impl::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_default_context();
}

ILibPtr LibraryFacade::create_default_lib()
{
  auto libFactory = lib0impl::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_default_lib();
}

ILibPtr LibraryFacade::create_library(LibraryContextPtr ctx)
{
  auto libFactory = lib0impl::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_appropriate_lib(ctx);
}

}  // namespace templatelib0
