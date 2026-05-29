#include "src/gtkmm4/gl-area/GLTriangleArea.h"

#include <epoxy/gl.h>

#include "src/log/log.h"

namespace Gtkmm4i::gl_area
{

GLTriangleArea::GLTriangleArea()
{
  set_expand(true);
  set_size_request(320, 240);
  set_auto_render(true);

  signal_realize().connect(sigc::mem_fun(*this, &GLTriangleArea::on_area_realize));
  // unrealize before the default handler so the GL context is still current
  signal_unrealize().connect(
      sigc::mem_fun(*this, &GLTriangleArea::on_area_unrealize), false);
  signal_render().connect(sigc::mem_fun(*this, &GLTriangleArea::on_area_render),
                          false);
}

GLTriangleArea::~GLTriangleArea() = default;

void GLTriangleArea::on_area_realize()
{
  make_current();

  try {
    throw_if_error();
  }
  catch (const Gdk::GLError& gle) {
    LOGE("Failed to realize the Gtk::GLArea GL context: " << gle.what());
    return;
  }

  // The GL context is now current. Allocate your buffers, shaders and other
  // GL resources here.
}

void GLTriangleArea::on_area_unrealize()
{
  make_current();

  try {
    throw_if_error();
  }
  catch (const Gdk::GLError&) {
    return;
  }

  // Release any GL resources allocated in on_area_realize() here.
}

bool GLTriangleArea::on_area_render(const Glib::RefPtr<Gdk::GLContext>& /*ctx*/)
{
  try {
    throw_if_error();
  }
  catch (const Gdk::GLError& gle) {
    LOGE("Gtk::GLArea render error: " << gle.what());
    return false;
  }

  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);

  // Blank black canvas. Enter your own OpenGL draw commands below to render a
  // scene into the Gtk::GLArea framebuffer.
  LOGI("Gtk::GLArea blank frame rendered - add your OpenGL commands in "
       "GLTriangleArea::on_area_render()");

  glFlush();

  return true;
}

}  // namespace Gtkmm4i::gl_area
