#include "src/gtkmm4/main-window/GtkmmWindow.h"

#include <string>

#include "project-global-decls.h"
#include "src/log/log.h"
#include "src/vulkan/dmabuf/DmabufFrame.h"
#include "src/vulkan/dmabuf/VulkanDmabufRenderer.h"

namespace Gtkmm4i::main_window
{

GtkmmWindow::GtkmmWindow()
{
  if (!init()) {
    LOGE("Fail to init");
  }
}

GtkmmWindow::~GtkmmWindow() = default;

bool GtkmmWindow::init()
{
  set_title(get_default_title());
  set_default_size(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);

  if (!show_vulkan_surface()) {
    LOGI(
        "Vulkan dma-buf surface unavailable; showing a plain black window "
        "instead");
    show_fallback_black();
  }

  return true;
}

bool GtkmmWindow::show_vulkan_surface()
{
  renderer = vulkani::VulkanDmabufRenderer::create(
      static_cast<std::uint32_t>(W_DEFAULT_WIDTH),
      static_cast<std::uint32_t>(W_DEFAULT_HEIGHT), 0.0F, 0.0F, 0.0F, 1.0F);

  if (renderer == nullptr || !renderer->frame().has_value()) {
    renderer.reset();
    return false;
  }

  Glib::RefPtr<Gdk::Texture> texture = build_texture(renderer->frame().value());

  if (!texture) {
    renderer.reset();
    return false;
  }

  picture.set_paintable(texture);
  // Fill the whole window with the Vulkan frame (no theme colored letterboxing).
  picture.set_content_fit(Gtk::ContentFit::FILL);
  set_child(picture);

  return true;
}

Glib::RefPtr<Gdk::Texture> GtkmmWindow::build_texture(
    const vulkani::DmabufFrame& frame)
{
  try {
    auto builder = Gdk::DmabufTextureBuilder::create();
    builder->set_display(Gdk::Display::get_default());
    builder->set_width(frame.width);
    builder->set_height(frame.height);
    builder->set_fourcc(frame.fourcc);
    builder->set_modifier(frame.modifier);
    builder->set_n_planes(1);
    builder->set_fd(0, frame.fd);
    builder->set_stride(0, frame.stride);
    builder->set_offset(0, frame.offset);

    // No release slot: the renderer keeps the file descriptor (and the backing
    // Vulkan memory) alive for its whole lifetime, which outlives this texture.
    return builder->build();
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to build the Vulkan dma-buf texture: " << ex.what());
    return {};
  }
}

void GtkmmWindow::show_fallback_black()
{
  auto css_provider = Gtk::CssProvider::create();

  try {
    css_provider->load_from_resource(main_css_res_path);
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to load CSS: " << ex.what());
    return;
  }

  auto display = Gdk::Display::get_default();
  Gtk::StyleProvider::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

const std::string& GtkmmWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

GtkmmWindowPtr GtkmmWindow::create() { return std::make_shared<GtkmmWindow>(); }

}  // namespace Gtkmm4i::main_window
