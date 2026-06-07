#include "src/gtkmm4/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/main-window/GtkmmWindow.h"
#include "src/log/log.h"
#include "src/vulkan/VulkanController.h"

namespace Gtkmm4i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  // The Vulkan work is headless (raw libvulkan, no GTK dependency): create an
  // instance, enumerate the physical devices and log their properties before
  // the GTK main loop is entered. GTK4 exposes no usable Vulkan rendering widget
  // (see GtkmmWindow), so the window itself is a plain, blank black GTK window.
  vulkani::VulkanControllerPtr vulkan = vulkani::VulkanController::create();

  if (vulkan == nullptr) {
    LOGE("Fail to create the Vulkan controller");
    return app::IApplication::INVALID;
  }

  if (!vulkan->run(actx)) {
    LOGE("Failed to enumerate the Vulkan physical devices");
    return app::IApplication::INVALID;
  }

  LOGD("Trying to create the GTK4 app instance");

  auto app = Gtk::Application::create(project_decls::PROJECT_REVERSE_URL);

  LOGD("Starting the GTK4 app");

  return app->make_window_and_run<main_window::GtkmmWindow>(actx->argc,
                                                            actx->argv);
}

}  // namespace Gtkmm4i
