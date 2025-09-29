#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_UI_EVENTS_HANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_UI_EVENTS_HANDLER_CLASS_H

#include <memory>

#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/main-window/Loader.h"

namespace Gtkmm3i::main_window
{

/**
 * @brief The root GTKmm3 window events handler class.
 * Which must contain all the main window events handlers.
 */
class EventsHandler
{
 public:
  using EventsHandlerPtr = std::shared_ptr<EventsHandler>;

  virtual ~EventsHandler() = default;
  EventsHandler() = default;

  static EventsHandlerPtr create();

  virtual bool init(LoaderPtr loader);
};

using EventsHandlerPtr = EventsHandler::EventsHandlerPtr;

}  // namespace Gtkmm3i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_UI_EVENTS_HANDLER_CLASS_H
