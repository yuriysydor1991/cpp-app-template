#include "src/lib/libmain/LibFactory.h"

#include <cassert>
#include <memory>

#include "src/lib/libmain/LibMain.h"

namespace lib0impl
{

LibFactory::ILibPtr LibFactory::create_default_lib()
{
  return LibMain::create();
}

LibFactory::LibraryContextPtr LibFactory::create_default_context()
{
  return std::make_shared<LibraryContext>();
}

LibFactory::ILibPtr LibFactory::create_appropriate_lib(
    [[maybe_unused]] LibraryContextPtr ctx)
{
  assert(ctx != nullptr);

  return create_default_lib();
}

LibFactoryPtr LibFactory::create_factory()
{
  return std::make_shared<LibFactory>();
}

}  // namespace lib0impl
