#include "src/qt6/Qt6Initer.h"

#include <cassert>

#include <QGuiApplication>

#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/qtvulkan/QtVulkanController.h"

namespace Qt6i
{

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  // QVulkanInstance (Qt6::Gui) obtains the platform Vulkan instance through the
  // platform integration, which requires a living QGuiApplication. No event
  // loop (app.exec()) is required: the controller creates the instance,
  // enumerates the physical devices, logs them through the LOGI calls in the
  // device info handler and returns.
  QGuiApplication app(actx->argc, actx->argv);

  qtvulkani::QtVulkanControllerPtr vulkan = qtvulkani::QtVulkanController::create();

  if (vulkan == nullptr) {
    LOGE("Fail to create the Qt Vulkan controller");
    return app::IApplication::INVALID;
  }

  if (!vulkan->run()) {
    LOGE("Failed to enumerate the Vulkan physical devices");
    return app::IApplication::INVALID;
  }

  return 0;
}

}  // namespace Qt6i
