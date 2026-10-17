#include "src/app/signals-handlers/handlers/posix/PauseSignalsHandler.h"

#include <atomic>
#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

PauseSignalsHandler::~PauseSignalsHandler()
{
  PauseSignalsHandler::uninstall();
}

const std::set<int>& PauseSignalsHandler::get_handled_signals()
{
  // Place here the OS signals that are asking the application to pause. Every
  // one of them is a POSIX only signal, so the whole set stays an empty one on
  // the platforms which are not declaring them, like the MS Windows one. The
  // SIGSTOP one is deliberately absent here, since the OS suspends the process
  // on it without giving any process a chance to handle it. So are the SIGTTIN
  // and the SIGTTOU ones of a background process touching the terminal: the
  // terminal access is retried after a returning handler, so a handled one
  // spins forever instead of letting the shell job control suspend it.
  static const std::set<int> pauseSignals{
#ifdef SIGTSTP
      SIGTSTP,  // The Ctrl+Z keys combination of the terminal.
#endif          // SIGTSTP
  };

  return pauseSignals;
}

SignalDisposition PauseSignalsHandler::get_signal_disposition()
{
  return &PauseSignalsHandler::pause_context;
}

void PauseSignalsHandler::store_context(ApplicationContext* ctx)
{
  mhandled_context.store(ctx);
}

void PauseSignalsHandler::pause_context([[maybe_unused]] int signalNumber)
{
  ApplicationContext* const ctx = mhandled_context.load();

  if (ctx != nullptr) {
    ctx->set_pause(true);
  }
}

}  // namespace app
