#include "src/qt6/Qt6Initer.h"

#include <cassert>

#include <QApplication>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

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
  // platform integration, which requires a living Q(Gui)Application.
  QApplication app(actx->argc, actx->argv);

  qtvulkani::QtVulkanControllerPtr vulkan =
      qtvulkani::QtVulkanController::create();

  if (vulkan == nullptr) {
    LOGE("Fail to create the Qt Vulkan controller");
    return app::IApplication::INVALID;
  }

  if (!vulkan->run()) {
    LOGE("Failed to enumerate the Vulkan physical devices");
    return app::IApplication::INVALID;
  }

  // The Vulkan surface lives in a QVulkanWindow, which is a bare QWindow. Shown
  // on its own a top level QWindow is not reliably given window manager
  // decorations (no title bar, borders or controls), so it is hosted inside a
  // top level QWidget through QWidget::createWindowContainer(): the widget is a
  // normal decorated application window and the Vulkan surface fills its client
  // area. The QVulkanWindow is reparented into (and destroyed with) the
  // container and reuses the controller's already validated instance.
  auto* vulkanWindow = new qtvulkani::BlankVulkanWindow;
  vulkanWindow->setVulkanInstance(vulkan->vulkan_instance());

  QWidget topLevel;
  topLevel.setWindowTitle(QString::fromStdString(
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION));
  topLevel.resize(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);

  auto* layout = new QVBoxLayout(&topLevel);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(QWidget::createWindowContainer(vulkanWindow, &topLevel));

  topLevel.show();

  return app.exec();
}

}  // namespace Qt6i
