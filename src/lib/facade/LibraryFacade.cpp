#include "LibraryFacade.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-lib-decls.h"
#include "src/lib/libmain/LibFactory.h"
#include "src/log/log.h"

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

void LibraryFacade::init_logger(const logger::ILoggerPtr& appLogger)
{
  LOG_INIT_REAL_LOGGER(appLogger);
}

}  // namespace TEMPLATE_LIB_NAMESPACE
