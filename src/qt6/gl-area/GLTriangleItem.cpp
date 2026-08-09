#include "src/qt6/gl-area/GLTriangleItem.h"

#include "src/log/log.h"
#include "src/qt6/gl-area/GLTriangleRenderer.h"

namespace Qt6i::gl_area
{

GLTriangleItem::GLTriangleItem(QQuickItem* parent)
    : QQuickFramebufferObject{parent}
{
  // OpenGL fills its framebuffer bottom row first, while the scene graph draws
  // the texture top row first, so the framebuffer is flipped back here.
  setMirrorVertically(true);
}

GLTriangleItem::~GLTriangleItem() = default;

QQuickFramebufferObject::Renderer* GLTriangleItem::createRenderer() const
{
  LOGD("Creating the QQuickFramebufferObject OpenGL renderer");

  return new GLTriangleRenderer;
}

}  // namespace Qt6i::gl_area
