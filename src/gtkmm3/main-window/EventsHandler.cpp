#include "src/gtkmm3/main-window/EventsHandler.h"

#include <memory>
#include <cassert>

#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/main-window/Loader.h"
#include "src/log/log.h"

namespace Gtkmm3i::main_window
{

EventsHandlerPtr EventsHandler::create()
{
  return std::make_shared<EventsHandler>();
}

bool EventsHandler::init([[maybe_unused]] LoaderPtr loader)
{
  assert(loader != nullptr);

  if (loader == nullptr) {
    LOGE("Invalid window loader pointer provided");
    return false;
  }

  LOGD("Put the main window events connections here");

  return true;
}

}  // namespace Gtkmm3i::main_window
