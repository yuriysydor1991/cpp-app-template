#include "src/app/signals-handlers/SignalsHandler.h"

#include <atomic>
#include <cassert>
#include <csignal>
#include <memory>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/log/log.h"

namespace app
{

static_assert(std::atomic<ApplicationContext*>::is_always_lock_free,
              "The signal handler may touch the lock free atomics only");

SignalsHandler::~SignalsHandler() { SignalsHandler::uninstall(); }

bool SignalsHandler::install(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  uninstall();

  mstopping_context.store(ctx.get());

  for (const int signalNumber : get_handled_signals()) {
    if (std::signal(signalNumber, &SignalsHandler::stop_context) == SIG_ERR) {
      LOGE("Fail to handle the signal " << signalNumber);
      continue;
    }

    minstalled_signals.emplace(signalNumber);
  }

  LOGD("Handling " << minstalled_signals.size() << " application stop signals");

  return !minstalled_signals.empty();
}

void SignalsHandler::uninstall()
{
  if (minstalled_signals.empty()) {
    return;
  }

  for (const int signalNumber : minstalled_signals) {
    std::signal(signalNumber, SIG_DFL);
  }

  minstalled_signals.clear();
  mstopping_context.store(nullptr);
}

const std::set<int>& SignalsHandler::get_handled_signals()
{
  // Place here the OS signals that are asking the application to stop. The
  // ones the C++ standard does not declare are guarded with the ifdef.
  static const std::set<int> stopSignals{
      SIGINT,
      SIGTERM,
#ifdef SIGHUP
      SIGHUP,
#endif  // SIGHUP
#ifdef SIGQUIT
      SIGQUIT,
#endif  // SIGQUIT
  };

  return stopSignals;
}

void SignalsHandler::stop_context([[maybe_unused]] int signalNumber)
{
  ApplicationContext* const ctx = mstopping_context.load();

  if (ctx != nullptr) {
    ctx->set_stop(true);
  }
}

}  // namespace app
