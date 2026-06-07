#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H

#include <memory>
#include <string>

#include "src/gtkmm4/gtkmm4_includes.h"

namespace vulkani
{
struct DmabufFrame;
class VulkanDmabufRenderer;
}  // namespace vulkani

namespace Gtkmm4i::main_window
{

/**
 * @brief The root GTKmm4 window showing genuine Vulkan output.
 *
 * GTK4 exposes no Vulkan rendering widget, so this window renders a cleared
 * (black) frame with Vulkan into an off-screen image, exports it as a Linux
 * dma-buf and displays it through a Gdk::DmabufTexture in a Gtk::Picture - the
 * supported way to put Vulkan output on the GTK stack. When the dma-buf path is
 * unavailable (no Vulkan device, missing extensions, or a software ICD such as
 * lavapipe), it falls back to a plain black window painted through an embedded
 * CSS resource, so a blank black window is shown either way.
 */
class GtkmmWindow : public Gtk::Window
{
 public:
  using GtkmmWindowPtr = std::shared_ptr<GtkmmWindow>;

  GtkmmWindow();
  ~GtkmmWindow() override;

  bool init();

  static GtkmmWindowPtr create();

 protected:
  const std::string& get_default_title();

 private:
  /**
   * @brief Tries to render a Vulkan frame, export it and show it.
   *
   * @return Returns true when the Vulkan dma-buf texture is shown and false
   * when the dma-buf path is unavailable and the caller should fall back.
   */
  bool show_vulkan_surface();

  /**
   * @brief Paints the window black through the embedded CSS resource.
   */
  void show_fallback_black();

  /**
   * @brief Wraps an exported dma-buf into a Gdk texture.
   *
   * @param frame The exported dma-buf description.
   *
   * @return The created texture, or an empty pointer on failure.
   */
  Glib::RefPtr<Gdk::Texture> build_texture(const vulkani::DmabufFrame& frame);

  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";

  inline static constexpr const int W_DEFAULT_WIDTH = 650;
  inline static constexpr const int W_DEFAULT_HEIGHT = 400;

  // Declared before the picture so it (and the dma-buf it owns) outlives the
  // texture held by the picture.
  std::unique_ptr<vulkani::VulkanDmabufRenderer> renderer;

  Gtk::Picture picture;
};

using GtkmmWindowPtr = GtkmmWindow::GtkmmWindowPtr;

}  // namespace Gtkmm4i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
