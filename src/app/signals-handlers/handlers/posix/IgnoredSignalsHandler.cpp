#include "src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.h"

#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

IgnoredSignalsHandler::~IgnoredSignalsHandler()
{
  IgnoredSignalsHandler::uninstall();
}

const std::set<int>& IgnoredSignalsHandler::get_handled_signals()
{
  // Place here the OS signals the application deliberately ignores. The POSIX
  // only SIGPIPE one arrives on a write into a pipe or a socket nobody reads
  // any more and terminates the process by default.
  static const std::set<int> ignoredSignals{
#ifdef SIGPIPE
      SIGPIPE,
#endif  // SIGPIPE
  };

  return ignoredSignals;
}

SignalDisposition IgnoredSignalsHandler::get_signal_disposition()
{
  return SIG_IGN;
}

void IgnoredSignalsHandler::store_context(
    [[maybe_unused]] ApplicationContext* ctx)
{
  // Deliberately empty: an ignored signal reaches no routine of the current
  // class, so there is nothing to hand the context over to.
}

}  // namespace app
