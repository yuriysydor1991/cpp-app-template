#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H

#include <memory>
#include <vector>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

/**
 * @brief The facade of the whole signals handlers component, which covers
 * every OS signals category of the application with a single
 * ISignalsHandler::install call.
 *
 * The class implements the very same ISignalsHandler interface its
 * subhandlers do, so the rest of the application depends on the interface
 * only and neither knows how many categories exist nor which platform
 * declares them. The covered categories are the ones the
 * SignalsHandler::create_handlers method creates, which are the
 * StopSignalsHandler, the PauseSignalsHandler, the ContinueSignalsHandler, the
 * ReloadSignalsHandler, the UserSignalsHandler and the IgnoredSignalsHandler
 * ones by default.
 */
class SignalsHandler : public ISignalsHandler
{
 public:
  /// @brief Releases the subhandlers with the own SignalsHandler
  /// implementation of the ISignalsHandler::uninstall method.
  ~SignalsHandler() override;
  SignalsHandler() = default;

  /**
   * @brief Creates the SignalsHandler::create_handlers subhandlers and hands
   * the given context over to the ISignalsHandler::install method of every one
   * of them. See the ISignalsHandler interface.
   *
   * @param ctx The context to hand over to the subhandlers.
   *
   * @return Returns true if at least one subhandler covers its signals from
   * now on and false in case of any error. A subhandler which covers no
   * signals on the current platform is not an error on its own, so the whole
   * facade still reports a success as long as any other one succeeds.
   */
  virtual bool install(std::shared_ptr<ApplicationContext> ctx) override;

  /// @brief Calls the ISignalsHandler::uninstall method of every created
  /// subhandler and releases them. See the ISignalsHandler interface.
  virtual void uninstall() override;

 protected:
  /**
   * @brief Method should create a subhandler of every OS signals category the
   * application covers.
   *
   * Add a newly written category handler here and the whole application gets
   * it covered, since nothing else creates the subhandlers.
   *
   * @return The created subhandlers, an empty vector in case of any error.
   */
  virtual std::vector<std::shared_ptr<ISignalsHandler>> create_handlers();

 private:
  /// @brief The subhandlers of the latest SignalsHandler::install call, which
  /// are to be released by the SignalsHandler::uninstall method.
  std::vector<std::shared_ptr<ISignalsHandler>> mhandlers;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H
