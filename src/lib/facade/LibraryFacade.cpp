#include "LibraryFacade.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-lib-decls.h"
#include "src/lib/libmain/LibFactory.h"

namespace TEMPLATE_LIB_NAMESPACE
{

LibraryContextPtr LibraryFacade::create_library_context()
{
  auto libFactory = TEMPLATE_LIB_IMPL_NAMESPACE::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_default_context();
}

ILibPtr LibraryFacade::create_default_lib()
{
  auto libFactory = TEMPLATE_LIB_IMPL_NAMESPACE::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_default_lib();
}

ILibPtr LibraryFacade::create_library(LibraryContextPtr ctx)
{
  auto libFactory = TEMPLATE_LIB_IMPL_NAMESPACE::LibFactory::create_factory();

  assert(libFactory != nullptr);

  return libFactory->create_appropriate_lib(ctx);
}

}  // namespace TEMPLATE_LIB_NAMESPACE
