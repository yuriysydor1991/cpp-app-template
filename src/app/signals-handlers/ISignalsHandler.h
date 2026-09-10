#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ISIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ISIGNALSHANDLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace app
{

/**
 * @brief Class interface to be implemented by all the OS signals handlers.
 *
 * An implementor subscribes the process to the OS signals it covers and
 * touches the given application context as soon as any of them arrives, which
 * means to ask the context to stop with the ApplicationContext::set_stop
 * setter, to pause with the ApplicationContext::set_pause one and so on.
 *
 * The interface is implemented by the single category handlers, like the
 * StopSignalsHandler one, as well as by the SignalsHandler facade which
 * forwards it's calls to all of them, so a user of the interface depends on
 * neither the covered categories count nor the platform which declares them.
 */
class ISignalsHandler
{
 public:
  virtual ~ISignalsHandler() = default;
  ISignalsHandler() = default;

  /**
   * @brief Subscribes the process to the covered OS signals.
   *
   * @param ctx The context to touch once a covered signal arrives. The context
   * must outlive the current instance.
   *
   * @return Implementors should return a true value if at least one signal is
   * covered from now on and a false one in case of any error.
   */
  virtual bool install(std::shared_ptr<ApplicationContext> ctx) = 0;

  /**
   * @brief Restores the default OS reaction on the covered signals and forgets
   * the context given to the ISignalsHandler::install method. Implementors
   * must call it from their destructor, so an explicit call is only needed to
   * stop the handling earlier.
   */
  virtual void uninstall() = 0;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ISIGNALSHANDLER_CLASS_H
