#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H

#include <atomic>
#include <memory>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

/**
 * @brief The default OS signals handler which raises the application context
 * stop flag on every process termination request like the Ctrl+C one.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest SignalsHandler::install
 * call is the one that gets stopped.
 */
class SignalsHandler : public ISignalsHandler
{
 public:
  /// @brief Releases the handled signals with the own SignalsHandler
  /// implementation of the ISignalsHandler::uninstall method.
  ~SignalsHandler() override;
  SignalsHandler() = default;

  /**
   * @brief Makes the SignalsHandler::stop_context routine the handler of every
   * SignalsHandler::get_handled_signals signal. See the ISignalsHandler
   * interface.
   *
   * @param ctx The context to stop once a handled signal arrives.
   *
   * @return Returns true if at least one signal is handled from now on and
   * false in case of any error.
   */
  virtual bool install(std::shared_ptr<ApplicationContext> ctx) override;

  /// @brief Gives the handled signals back to the OS default disposition. See
  /// the ISignalsHandler interface.
  virtual void uninstall() override;

 protected:
  /**
   * @brief Method should return the set of the OS signals numbers that are
   * asking the application to stop.
   */
  virtual const std::set<int>& get_handled_signals();

  /**
   * @brief The routine the OS calls in the signal context, so it touches the
   * lock free atomics only and does no logging, since nothing else is async
   * signal safe.
   *
   * @param signalNumber The arrived signal number given by the OS.
   */
  static void stop_context(int signalNumber);

 private:
  /// @brief The context to stop, kept as a plain pointer, since neither the
  /// std::signal handler accepts a user data argument nor the std::shared_ptr
  /// is async signal safe.
  inline static std::atomic<ApplicationContext*> mstopping_context{nullptr};

  /// @brief The signals that are handled by the current instance and are to be
  /// released by the SignalsHandler::uninstall method.
  std::set<int> minstalled_signals;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SIGNALSHANDLER_CLASS_H
