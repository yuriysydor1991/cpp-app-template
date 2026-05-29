#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_GLTRIANGLEAREA_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_GLTRIANGLEAREA_CLASS_H

#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::gl_area
{

/**
 * @brief A minimal, self-contained OpenGL widget built on top of the native
 * GTKmm-4 Gtk::GLArea. It wires up the realize/render/unrealize GL resource
 * life cycle and clears the framebuffer to black every frame, leaving a blank
 * canvas. Add your own OpenGL commands inside on_area_render() (and allocate
 * any resources in on_area_realize()) to draw a real scene.
 */
class GLTriangleArea : public Gtk::GLArea
{
 public:
  GLTriangleArea();
  ~GLTriangleArea() override;

 protected:
  /** @brief Prepare GL resources once the GL context is available. */
  void on_area_realize();
  /** @brief Release GL resources before the GL context is destroyed. */
  void on_area_unrealize();
  /** @brief Draw a single frame into the Gtk::GLArea framebuffer. */
  bool on_area_render(const Glib::RefPtr<Gdk::GLContext>& context);
};

}  // namespace Gtkmm4i::gl_area

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_GLTRIANGLEAREA_CLASS_H
