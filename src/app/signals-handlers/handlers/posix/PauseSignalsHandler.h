#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PAUSESIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PAUSESIGNALSHANDLER_CLASS_H

#include <atomic>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the POSIX signals which are asking the process to
 * suspend itself, like the SIGTSTP one of the Ctrl+Z keys combination.
 *
 * Every covered signal raises the application context pause flag through the
 * ApplicationContext::set_pause setter, so the application is expected to poll
 * the ApplicationContext::get_pause one and to hold its work while the flag is
 * raised, instead of leaving its IApplication::run implementation. The
 * ContinueSignalsHandler class is the one that lowers the very same flag back.
 *
 * **Handling the covered signals replaces the OS default disposition of them,
 * so the process is not suspended by the Ctrl+Z keys combination any more** -
 * it is up to the application to react on the raised pause flag.
 *
 * The SIGSTOP signal is deliberately not covered, since no process is allowed
 * to handle, to block or to ignore it at all, so the OS suspension it causes
 * stays unnoticed by the application.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest ISignalsHandler::install
 * call is the one that gets paused.
 */
class PauseSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~PauseSignalsHandler() override;
  PauseSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers that are asking the application to
  /// pause. See the ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the PauseSignalsHandler::pause_context routine. See the
  /// ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps the given context in the
  /// PauseSignalsHandler::mhandled_context field. See the ASignalsHandler
  /// class.
  virtual void store_context(ApplicationContext* ctx) override;

  /**
   * @brief The routine the OS calls in the signal context, so it touches the
   * lock free atomics only and does no logging, since nothing else is async
   * signal safe.
   *
   * @param signalNumber The arrived signal number given by the OS.
   */
  static void pause_context(int signalNumber);

 private:
  /// @brief The context to pause, kept as a plain pointer, since neither the
  /// std::signal handler accepts a user data argument nor the std::shared_ptr
  /// is async signal safe.
  inline static std::atomic<ApplicationContext*> mhandled_context{nullptr};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAUSESIGNALSHANDLER_CLASS_H
