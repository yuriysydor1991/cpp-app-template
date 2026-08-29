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
    // Only the own default logger instance is initialized here. The logging
    // destination of an adopted one belongs to the code which uses the
    // library, so the library must not replace the log file, the level nor the
    // printing settings chosen by it. See the
    // CppAppTemplate012::LibraryFacade::init_logger method.
    LOG_INIT_DEFAULTS_IF_OWN();
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
