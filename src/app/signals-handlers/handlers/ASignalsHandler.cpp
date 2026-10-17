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

  bool anyCovered{false};

  for (const int signalNumber : get_handled_signals()) {
    const SignalDisposition previous =
        std::signal(signalNumber, signalDisposition);

    if (previous == SIG_ERR) {
      LOGE("Fail to handle the signal " << signalNumber);
      continue;
    }

    anyCovered = true;

    // An inherited ignored signal (nohup, the background jobs) stays ignored.
    if (previous == SIG_IGN && signalDisposition != SIG_IGN) {
      std::signal(signalNumber, SIG_IGN);
      continue;
    }

    mprevious_dispositions.emplace(signalNumber, previous);
  }

  if (!anyCovered) {
    store_context(nullptr);
    return false;
  }

  LOGD("Handling " << mprevious_dispositions.size() << " OS signals");

  return true;
}

void ASignalsHandler::uninstall()
{
  for (const auto& [signalNumber, previous] : mprevious_dispositions) {
    std::signal(signalNumber, previous);
  }

  mprevious_dispositions.clear();

  store_context(nullptr);
}

}  // namespace app
