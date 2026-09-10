#include "src/app/signals-handlers/handlers/posix/UserSignalsHandler.h"

#include <atomic>
#include <csignal>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

UserSignalsHandler::~UserSignalsHandler() { UserSignalsHandler::uninstall(); }

const std::set<int>& UserSignalsHandler::get_handled_signals()
{
  // Place here the OS signals that carry no meaning of their own and are
  // reserved for the application needs. Both of them are the POSIX only ones,
  // so the whole set stays an empty one on the platforms which are not
  // declaring them, like the MS Windows one.
  static const std::set<int> userSignals{
#ifdef SIGUSR1
      SIGUSR1,
#endif  // SIGUSR1
#ifdef SIGUSR2
      SIGUSR2,
#endif  // SIGUSR2
  };

  return userSignals;
}

SignalDisposition UserSignalsHandler::get_signal_disposition()
{
  return &UserSignalsHandler::request_context;
}

void UserSignalsHandler::store_context(ApplicationContext* ctx)
{
  mhandled_context.store(ctx);
}

void UserSignalsHandler::request_context([[maybe_unused]] int signalNumber)
{
  // The ifdef guarded branches below are the only ones which write through
  // the pointer, so a platform declaring none of the covered signals leaves it
  // read only.
  // cppcheck-suppress constVariablePointer
  ApplicationContext* const ctx = mhandled_context.load();

  if (ctx == nullptr) {
    return;
  }

  // Map a newly covered user signal to its own context request flag here.
#ifdef SIGUSR1
  if (signalNumber == SIGUSR1) {
    ctx->set_first_user_request(true);
    return;
  }
#endif  // SIGUSR1

#ifdef SIGUSR2
  if (signalNumber == SIGUSR2) {
    ctx->set_second_user_request(true);
    return;
  }
#endif  // SIGUSR2
}

}  // namespace app
