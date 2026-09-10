#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_POSIXSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_POSIXSIGNALSHANDLER_CLASS_H

#include <atomic>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/ASignalsHandler.h"

namespace app
{

/**
 * @brief The common base of every signals category handler of the POSIX
 * platforms family, so the platform a handler belongs to is a part of its type
 * and not a directory name only.
 *
 * The class adds no behaviour of its own to the inherited ASignalsHandler one
 * on purpose. It classifies the descendants instead, which lets the rest of
 * the project tell the platform family of a handler apart, keeps a place for
 * the helpers the whole family may share one day and makes a handler of a
 * different family - a MS Windows console control one, for example - an
 * obviously different type rather than a look alike neighbour.
 *
 * The covered signals are the ones the standard `csignal` header and the POSIX
 * platforms declare, so the descendants stay compilable everywhere, while the
 * signals which the current platform does not declare are guarded with the
 * ifdef and are simply left uncovered there.
 *
 * @see ASignalsHandler for the install and uninstall mechanics and for the
 * methods a descendant is expected to override.
 */
class PosixSignalsHandler : public ASignalsHandler
{
 public:
  /**
   * @brief The destructor releases no signals, the same way the
   * ASignalsHandler one does not, so every descendant is still the one to call
   * the ISignalsHandler::uninstall method from its own destructor.
   */
  ~PosixSignalsHandler() override;
  PosixSignalsHandler() = default;

 protected:
  // The whole family keeps the handled context in a lock free atomic, since
  // the routine the OS calls is allowed to use the async signal safe calls
  // only. The assertion covers every descendant at once.
  static_assert(std::atomic<ApplicationContext*>::is_always_lock_free,
                "The signal handler may touch the lock free atomics only");
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_POSIXSIGNALSHANDLER_CLASS_H
