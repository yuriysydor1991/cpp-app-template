#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H

#include <atomic>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the OS signals which are asking the process to
 * terminate, like the SIGINT one of the Ctrl+C keys combination.
 *
 * Every covered signal raises the application context stop flag through the
 * ApplicationContext::set_stop setter, so the application is expected to poll
 * the ApplicationContext::get_stop one and to return from its
 * IApplication::run implementation as soon as the flag is raised.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest ISignalsHandler::install
 * call is the one that gets stopped.
 */
class StopSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~StopSignalsHandler() override;
  StopSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers that are asking the application to
  /// stop. See the ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the StopSignalsHandler::stop_context routine. See the
  /// ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps the given context in the
  /// StopSignalsHandler::mhandled_context field. See the ASignalsHandler
  /// class.
  virtual void store_context(ApplicationContext* ctx) override;

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
  inline static std::atomic<ApplicationContext*> mhandled_context{nullptr};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H
