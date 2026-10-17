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

  // The Vulkan work is headless (raw libvulkan, no GTK dependency): the
  // controller creates the single instance of the application, enumerates the
  // physical devices and logs their properties before the GTK main loop is
  // entered. Without a usable Vulkan runtime (no loader, no driver) the window
  // still opens and shows its plain black fallback.
  vulkani::VulkanControllerPtr vulkan = vulkani::VulkanController::create();

  if (vulkan == nullptr) {
    LOGW("No Vulkan instance is available, the window falls back to black");
  } else if (!vulkan->run()) {
    LOGW("Failed to enumerate the Vulkan physical devices");
  }

  const VkInstance instance =
      vulkan != nullptr ? vulkan->vulkan_instance() : VK_NULL_HANDLE;

  LOGD("Trying to create the GTK4 app instance");

  auto app = Gtk::Application::create(project_decls::PROJECT_REVERSE_URL);

  const StopFlagWatcher stopWatcher{actx, *app};

  LOGD("Starting the GTK4 app");

  // The command line belongs to the CommandLineParser alone, so the toolkit
  // gets the program name only and never rejects the application parameters.
  // The window renders with the controller's instance, which outlives it.
  return app->make_window_and_run<main_window::GtkmmWindow>(
      std::min(actx->get_argc(), 1), actx->get_argv(), instance);
}

}  // namespace Gtkmm4i
