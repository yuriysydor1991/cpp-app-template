#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H

#include <memory>
#include <string>

#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::main_window
{

/**
 * @brief The root GTKmm4 window class showing a blank, black window.
 *
 * GTK4 exposes no Vulkan rendering widget (its toplevel surface is GTK managed
 * and the GdkVulkanContext API is deprecated and unwrapped by gtkmm), so this
 * branch keeps the Vulkan work headless (the physical device enumeration is
 * driven by the GtkmmIniter) and demonstrates a plain, blank black window - the
 * GTK counterpart of the blank black windows shown by the appSDL2 / appFreeGlut
 * branches. The black background is applied through an embedded CSS resource.
 */
class GtkmmWindow : public Gtk::Window
{
 public:
  using GtkmmWindowPtr = std::shared_ptr<GtkmmWindow>;

  virtual ~GtkmmWindow() = default;
  GtkmmWindow();

  bool init();

  static GtkmmWindowPtr create();

 protected:
  const std::string& get_default_title();

 private:
  void prepare_window();
  void prepare_css();

  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";

  inline static constexpr const int W_DEFAULT_WIDTH = 650;
  inline static constexpr const int W_DEFAULT_HEIGHT = 400;
};

using GtkmmWindowPtr = GtkmmWindow::GtkmmWindowPtr;

}  // namespace Gtkmm4i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
