#include "src/lib/libmain/LibMain.h"

#include <cassert>
#include <iostream>
#include <memory>

namespace lib0impl
{

bool LibMain::libcall([[maybe_unused]] std::shared_ptr<LibraryContext> ctx)
{
  assert(ctx != nullptr);

  std::cout << "Your application's library implementation goes here!"
            << std::endl;

  return true;
}

}  // namespace lib0impl
