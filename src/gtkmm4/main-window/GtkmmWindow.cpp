#include "src/gtkmm4/main-window/GtkmmWindow.h"

#include <unistd.h>

#include <string>

#include "project-global-decls.h"
#include "src/log/log.h"
#include "src/vulkan/dmabuf/DmabufFrame.h"
#include "src/vulkan/dmabuf/VulkanDmabufRenderer.h"

namespace Gtkmm4i::main_window
{

GtkmmWindow::GtkmmWindow(VkInstance instance)
{
  if (!init(instance)) {
    LOGE("Fail to init");
  }
}

GtkmmWindow::~GtkmmWindow() = default;

bool GtkmmWindow::init(VkInstance instance)
{
  set_title(get_default_title());
  set_default_size(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);

  if (!show_vulkan_surface(instance)) {
    LOGI(
        "Vulkan dma-buf surface unavailable; showing a plain black window "
        "instead");
    show_fallback_black();
  }

  return true;
}

bool GtkmmWindow::show_vulkan_surface(VkInstance instance)
{
  renderer = vulkani::VulkanDmabufRenderer::create(
      instance, static_cast<std::uint32_t>(W_DEFAULT_WIDTH),
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
  // Fill the whole window with the Vulkan frame (no theme colored
  // letterboxing).
  picture.set_content_fit(Gtk::ContentFit::FILL);
  set_child(picture);

  return true;
}

Glib::RefPtr<Gdk::Texture> GtkmmWindow::build_texture(
    const vulkani::DmabufFrame& frame)
{
  // The texture gets a file descriptor of it's own, which GTK closes through
  // the release slot once it is done with the buffer, so the texture never
  // depends on the renderer outliving it.
  const int textureFd = dup(frame.fd);

  if (textureFd < 0) {
    LOGE("Failed to duplicate the Vulkan dma-buf file descriptor");
    return {};
  }

  try {
    auto builder = Gdk::DmabufTextureBuilder::create();
    builder->set_display(Gdk::Display::get_default());
    builder->set_width(frame.width);
    builder->set_height(frame.height);
    builder->set_fourcc(frame.fourcc);
    builder->set_modifier(frame.modifier);
    builder->set_n_planes(1);
    builder->set_fd(0, textureFd);
    builder->set_stride(0, frame.stride);
    builder->set_offset(0, frame.offset);

    return builder->build([textureFd]() { ::close(textureFd); });
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to build the Vulkan dma-buf texture: " << ex.what());
    ::close(textureFd);
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

}  // namespace Gtkmm4i::main_window
