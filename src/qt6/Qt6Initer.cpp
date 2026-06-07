#include "src/qt6/Qt6Initer.h"

#include <cassert>

#include <QGuiApplication>
#include <QString>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/qtvulkan/QtVulkanController.h"
#include "src/qtvulkan/window/BlankVulkanWindow.h"

namespace Qt6i
{

namespace
{
constexpr const int W_DEFAULT_WIDTH = 650;
constexpr const int W_DEFAULT_HEIGHT = 400;
}  // namespace

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  // QVulkanInstance (Qt6::Gui) obtains the platform Vulkan instance through the
  // platform integration, which requires a living QGuiApplication.
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

  // Reuse the controller's already validated instance for a blank, black
  // Vulkan rendered window. The window must not outlive the controller (it owns
  // the QVulkanInstance), which is guaranteed here: both live on this stack and
  // the window is destroyed first when run() returns after the event loop ends.
  qtvulkani::BlankVulkanWindow window;
  window.setVulkanInstance(vulkan->vulkan_instance());
  window.resize(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);
  window.setTitle(QString::fromStdString(project_decls::PROJECT_NAME + " " +
                                         project_decls::PROJECT_BUILD_VERSION));
  window.show();

  return app.exec();
}

}  // namespace Qt6i
