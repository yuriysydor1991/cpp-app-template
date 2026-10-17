#include "src/gtkmm4/Gtkmm4Controller.h"

#include <algorithm>
#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm4/StopFlagWatcher.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/log/GtkLogBridge.h"
#include "src/gtkmm4/main-window/GtkmmWindow.h"
#include "src/log/log.h"
#include "src/vulkan/VulkanController.h"

namespace Gtkmm4i
{

int Gtkmm4Controller::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  // Every message the toolkit reports lands in the application log from here
  // on. It is taken over before anything of the toolkit is touched, so the
  // complaints of it's own start up are caught as well.
  gtklog::GtkLogBridge::install();

  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  // The Vulkan work is headless (raw libvulkan, no GTK dependency): create an
  // instance, enumerate the physical devices and log their properties before
  // the GTK main loop is entered. GTK4 exposes no usable Vulkan rendering
  // widget (see GtkmmWindow), so the window itself is a plain, blank black GTK
  // window.
  vulkani::VulkanControllerPtr vulkan = vulkani::VulkanController::create();

  if (vulkan == nullptr) {
    LOGE("Fail to create the Vulkan controller");
    return app::IApplication::INVALID;
  }

  if (!vulkan->run()) {
    LOGE("Failed to enumerate the Vulkan physical devices");
    return app::IApplication::INVALID;
  }

  LOGD("Trying to create the GTK4 app instance");

  auto app = Gtk::Application::create(project_decls::PROJECT_REVERSE_URL);

  const StopFlagWatcher stopWatcher{actx, *app};

  LOGD("Starting the GTK4 app");

  // The command line belongs to the CommandLineParser alone, so the toolkit
  // gets the program name only and never rejects the application parameters.
  // The window renders with the controller's instance, which outlives it.
  return app->make_window_and_run<main_window::GtkmmWindow>(
      std::min(actx->get_argc(), 1), actx->get_argv(),
      vulkan->vulkan_instance());
}

}  // namespace Gtkmm4i
