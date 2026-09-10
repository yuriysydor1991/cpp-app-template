#include "src/app/signals-handlers/SignalsHandler.h"

#include <cassert>
#include <memory>
#include <vector>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/PauseSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/StopSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/UserSignalsHandler.h"
#include "src/log/log.h"

namespace app
{

SignalsHandler::~SignalsHandler() { SignalsHandler::uninstall(); }

bool SignalsHandler::install(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  uninstall();

  mhandlers = create_handlers();

  if (mhandlers.empty()) {
    LOGE("No signals handlers created");
    return false;
  }

  bool anyInstalled{false};

  for (const std::shared_ptr<ISignalsHandler>& handler : mhandlers) {
    assert(handler != nullptr);

    if (handler == nullptr) {
      LOGE("An invalid signals handler met");
      continue;
    }

    anyInstalled = handler->install(ctx) || anyInstalled;
  }

  if (!anyInstalled) {
    LOGE("None of the signals handlers covers its signals");
    return false;
  }

  LOGD("Handling the OS signals with " << mhandlers.size() << " handlers");

  return true;
}

void SignalsHandler::uninstall()
{
  for (const std::shared_ptr<ISignalsHandler>& handler : mhandlers) {
    if (handler == nullptr) {
      continue;
    }

    handler->uninstall();
  }

  mhandlers.clear();
}

std::vector<std::shared_ptr<ISignalsHandler>> SignalsHandler::create_handlers()
{
  // Place here a subhandler of every OS signals category the application
  // covers.
  return {
      std::make_shared<StopSignalsHandler>(),
      std::make_shared<PauseSignalsHandler>(),
      std::make_shared<ContinueSignalsHandler>(),
      std::make_shared<ReloadSignalsHandler>(),
      std::make_shared<UserSignalsHandler>(),
      std::make_shared<IgnoredSignalsHandler>(),
  };
}

}  // namespace app
