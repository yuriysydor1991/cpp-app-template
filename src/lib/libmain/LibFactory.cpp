#include "src/lib/libmain/LibFactory.h"

#include <cassert>
#include <memory>

#include "src/lib/libmain/LibMain.h"

namespace lib0impl
{

std::shared_ptr<LibFactory::ILib> LibFactory::create_default_lib()
{
  return std::make_shared<LibMain>();
}

std::shared_ptr<LibFactory::LibraryContext> LibFactory::create_default_context()
{
  return std::make_shared<LibraryContext>();
}

std::shared_ptr<LibFactory::ILib> LibFactory::create_appropriate_lib(
    [[maybe_unused]] std::shared_ptr<LibraryContext> ctx)
{
  assert(ctx != nullptr);

  return create_default_lib();
}

std::shared_ptr<LibFactory> LibFactory::create_factory()
{
  return std::make_shared<LibFactory>();
}

}  // namespace lib0impl