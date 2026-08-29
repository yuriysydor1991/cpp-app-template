#include "src/lib/libmain/LibMain.h"

#include <cassert>
#include <memory>

#include "src/log/log.h"

namespace lib0impl
{

LibMain::LibMain()
{
  // No logging initialization on purpose. The logging destination belongs to
  // the application which uses the library, not to the library itself: an
  // application which depends on many derived libraries would otherwise
  // collect a log file per every one of them. Accept the application logger
  // instance through the LOG_INIT_REAL_LOGGER macro instead.
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
