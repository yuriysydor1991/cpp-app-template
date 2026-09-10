#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_USERSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_USERSIGNALSHANDLER_CLASS_H

#include <atomic>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the POSIX signals which the OS reserves for the
 * application own needs - the SIGUSR1 and the SIGUSR2 ones.
 *
 * The SIGUSR1 signal raises the first user defined request flag through the
 * ApplicationContext::set_first_user_request setter and the SIGUSR2 one raises
 * the second through the ApplicationContext::set_second_user_request setter,
 * so the current class is the only one which tells the covered signals apart
 * by the number the OS gives to its routine.
 *
 * **The meaning of both requests is the application own one**, since the OS
 * defines none - reopening the log files after a rotation and dumping the
 * current state are the classic ones. The application is expected to poll the
 * flags, to serve the pending request and to lower the flag back on its own.
 *
 * The flags coalesce, so a burst of the very same signal is a single pending
 * request. Count the arrivals inside the routine instead whenever every single
 * one of them has to be served.
 *
 * The OS default reaction on both signals terminates the process, so handling
 * them here keeps the application alive on a `kill -USR1` command.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected and the context of the latest ISignalsHandler::install
 * call is the one that gets the requests.
 */
class UserSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~UserSignalsHandler() override;
  UserSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers which are reserved for the
  /// application own needs. See the ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the UserSignalsHandler::request_context routine. See the
  /// ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps the given context in the
  /// UserSignalsHandler::mhandled_context field. See the ASignalsHandler
  /// class.
  virtual void store_context(ApplicationContext* ctx) override;

  /**
   * @brief The routine the OS calls in the signal context, so it touches the
   * lock free atomics only and does no logging, since nothing else is async
   * signal safe.
   *
   * @param signalNumber The arrived signal number given by the OS, which tells
   * the first user defined request from the second one here.
   */
  static void request_context(int signalNumber);

 private:
  /// @brief The context to request, kept as a plain pointer, since neither the
  /// std::signal handler accepts a user data argument nor the std::shared_ptr
  /// is async signal safe.
  inline static std::atomic<ApplicationContext*> mhandled_context{nullptr};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_USERSIGNALSHANDLER_CLASS_H
