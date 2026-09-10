#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H

#include <atomic>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the OS signals which are asking the process to reread
 * its configuration, which is the SIGHUP one of a closed terminal and of the
 * daemon control tools.
 *
 * Every covered signal raises the application context reload flag through the
 * ApplicationContext::set_reload setter, so the application is expected to
 * poll the ApplicationContext::get_reload one, to reread its configuration and
 * to lower the flag back on its own.
 *
 * The SIGHUP signal is the conventional configuration reload request of the
 * long living processes, which is why it belongs here and not to the
 * StopSignalsHandler category. **The OS default reaction on it terminates the
 * process, so handling it here means a closed terminal does not end the
 * application any more** - drop the current class from the
 * SignalsHandler::create_handlers set, or move the SIGHUP number back to the
 * StopSignalsHandler::get_handled_signals set, whenever the termination is the
 * expected reaction.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest ISignalsHandler::install
 * call is the one that gets reloaded.
 */
class ReloadSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~ReloadSignalsHandler() override;
  ReloadSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers that are asking the application to
  /// reload its configuration. See the ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the ReloadSignalsHandler::reload_context routine. See the
  /// ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps the given context in the
  /// ReloadSignalsHandler::mhandled_context field. See the ASignalsHandler
  /// class.
  virtual void store_context(ApplicationContext* ctx) override;

  /**
   * @brief The routine the OS calls in the signal context, so it touches the
   * lock free atomics only and does no logging, since nothing else is async
   * signal safe.
   *
   * @param signalNumber The arrived signal number given by the OS.
   */
  static void reload_context(int signalNumber);

 private:
  /// @brief The context to reload, kept as a plain pointer, since neither the
  /// std::signal handler accepts a user data argument nor the std::shared_ptr
  /// is async signal safe.
  inline static std::atomic<ApplicationContext*> mhandled_context{nullptr};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H
