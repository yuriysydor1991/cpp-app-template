#include "src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.h"

#include <atomic>
#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

ContinueSignalsHandler::~ContinueSignalsHandler()
{
  ContinueSignalsHandler::uninstall();
}

const std::set<int>& ContinueSignalsHandler::get_handled_signals()
{
  // Place here the OS signals that are asking the paused application to
  // continue. The POSIX only SIGCONT one is sent by the fg and bg commands of
  // the shell job control.
  static const std::set<int> continueSignals{
#ifdef SIGCONT
      SIGCONT,
#endif  // SIGCONT
  };

  return continueSignals;
}

SignalDisposition ContinueSignalsHandler::get_signal_disposition()
{
  return &ContinueSignalsHandler::continue_context;
}

void ContinueSignalsHandler::store_context(ApplicationContext* ctx)
{
  mhandled_context.store(ctx);
}

void ContinueSignalsHandler::continue_context([[maybe_unused]] int signalNumber)
{
  ApplicationContext* const ctx = mhandled_context.load();

  if (ctx != nullptr) {
    ctx->set_pause(false);
  }
}

}  // namespace app
