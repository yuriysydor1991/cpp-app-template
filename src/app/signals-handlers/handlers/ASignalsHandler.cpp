#include "src/app/signals-handlers/handlers/ASignalsHandler.h"

#include <cassert>
#include <csignal>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/log/log.h"

namespace app
{

bool ASignalsHandler::install(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  const SignalDisposition signalDisposition = get_signal_disposition();

  assert(signalDisposition != nullptr);

  if (signalDisposition == nullptr) {
    LOGE("No valid signal disposition provided");
    return false;
  }

  uninstall();

  store_context(ctx.get());

  for (const int signalNumber : get_handled_signals()) {
    if (std::signal(signalNumber, signalDisposition) == SIG_ERR) {
      LOGE("Fail to handle the signal " << signalNumber);
      continue;
    }

    minstalled_signals.emplace(signalNumber);
  }

  if (minstalled_signals.empty()) {
    store_context(nullptr);
    return false;
  }

  LOGD("Handling " << minstalled_signals.size() << " OS signals");

  return true;
}

void ASignalsHandler::uninstall()
{
  for (const int signalNumber : minstalled_signals) {
    std::signal(signalNumber, SIG_DFL);
  }

  minstalled_signals.clear();

  store_context(nullptr);
}

}  // namespace app
