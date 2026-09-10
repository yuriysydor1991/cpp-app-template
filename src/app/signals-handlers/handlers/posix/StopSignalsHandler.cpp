#include "src/app/signals-handlers/handlers/posix/StopSignalsHandler.h"

#include <atomic>
#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

StopSignalsHandler::~StopSignalsHandler() { StopSignalsHandler::uninstall(); }

const std::set<int>& StopSignalsHandler::get_handled_signals()
{
  // Place here the OS signals that are asking the application to stop. The
  // ones the C++ standard does not declare are guarded with the ifdef. The
  // SIGHUP one belongs to the ReloadSignalsHandler category instead, since it
  // is the conventional configuration reload request.
  static const std::set<int> stopSignals{
      SIGINT,
      SIGTERM,
#ifdef SIGQUIT
      SIGQUIT,
#endif  // SIGQUIT
  };

  return stopSignals;
}

SignalDisposition StopSignalsHandler::get_signal_disposition()
{
  return &StopSignalsHandler::stop_context;
}

void StopSignalsHandler::store_context(ApplicationContext* ctx)
{
  mhandled_context.store(ctx);
}

void StopSignalsHandler::stop_context([[maybe_unused]] int signalNumber)
{
  ApplicationContext* const ctx = mhandled_context.load();

  if (ctx != nullptr) {
    ctx->set_stop(true);
  }
}

}  // namespace app
