#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H

#include <atomic>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the POSIX signals which are asking the suspended
 * process to continue, which is the SIGCONT one of the fg and bg shell job
 * control commands.
 *
 * Every covered signal lowers the application context pause flag through the
 * ApplicationContext::set_pause setter, so it resumes the work the
 * PauseSignalsHandler class asked to hold.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest ISignalsHandler::install
 * call is the one that gets continued.
 */
class ContinueSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~ContinueSignalsHandler() override;
  ContinueSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers that are asking the paused
  /// application to continue. See the ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the ContinueSignalsHandler::continue_context routine. See
  /// the ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps the given context in the
  /// ContinueSignalsHandler::mhandled_context field. See the ASignalsHandler
  /// class.
  virtual void store_context(ApplicationContext* ctx) override;

  /**
   * @brief The routine the OS calls in the signal context, so it touches the
   * lock free atomics only and does no logging, since nothing else is async
   * signal safe.
   *
   * @param signalNumber The arrived signal number given by the OS.
   */
  static void continue_context(int signalNumber);

 private:
  /// @brief The context to continue, kept as a plain pointer, since neither
  /// the std::signal handler accepts a user data argument nor the
  /// std::shared_ptr is async signal safe.
  inline static std::atomic<ApplicationContext*> mhandled_context{nullptr};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H
