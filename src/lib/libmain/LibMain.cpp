#include "src/lib/libmain/LibMain.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"

namespace lib0impl
{

bool LibMain::libcall([[maybe_unused]] std::shared_ptr<LibraryContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid library context provided");
    return false;
  }

  LOGI("Your application's library implementation goes here!");

  return true;
}

}  // namespace lib0impl
