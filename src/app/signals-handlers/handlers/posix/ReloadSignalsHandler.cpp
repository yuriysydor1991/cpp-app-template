#include "src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.h"

#include <atomic>
#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

ReloadSignalsHandler::~ReloadSignalsHandler()
{
  ReloadSignalsHandler::uninstall();
}

const std::set<int>& ReloadSignalsHandler::get_handled_signals()
{
  // Place here the OS signals that are asking the application to reread its
  // configuration. The POSIX only SIGHUP one arrives on a closed terminal and
  // is the conventional reload request of the long living processes.
  static const std::set<int> reloadSignals{
#ifdef SIGHUP
      SIGHUP,
#endif  // SIGHUP
  };

  return reloadSignals;
}

SignalDisposition ReloadSignalsHandler::get_signal_disposition()
{
  return &ReloadSignalsHandler::reload_context;
}

void ReloadSignalsHandler::store_context(ApplicationContext* ctx)
{
  mhandled_context.store(ctx);
}

void ReloadSignalsHandler::reload_context([[maybe_unused]] int signalNumber)
{
  ApplicationContext* const ctx = mhandled_context.load();

  if (ctx != nullptr) {
    ctx->set_reload(true);
  }
}

}  // namespace app
