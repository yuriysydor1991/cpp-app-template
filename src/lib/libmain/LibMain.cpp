#include "src/lib/libmain/LibMain.h"

#include <cassert>
#include <memory>

#include "src/log/log.h"

namespace lib0impl
{

LibMain::LibMain()
{
  static bool inited{false};

  if (!inited) {
    LOG_INIT_DEFAULTS();
    inited = true;
  }
}

bool LibMain::libcall([[maybe_unused]] LibraryContextPtr ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid library context pointer provided");
    return false;
  }

  LOGI("Your library implementation goes here!");

  return true;
}

LibMainPtr LibMain::create() { return std::make_shared<LibMain>(); }

}  // namespace lib0impl
