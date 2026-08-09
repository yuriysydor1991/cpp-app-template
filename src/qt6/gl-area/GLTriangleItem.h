#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLEITEM_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLEITEM_CLASS_H

#include <QQuickFramebufferObject>
#include <QQuickItem>

namespace Qt6i::gl_area
{

/**
 * @brief A minimal, self-contained QML item that renders with the raw OpenGL
 * calls. The QQuickFramebufferObject base class provides an offscreen
 * framebuffer that the Qt Quick scene graph draws as an ordinary textured
 * item, so the GL content participates in the QML layout like any other
 * element. The drawing itself is done by the GLTriangleRenderer instance
 * returned from createRenderer().
 *
 * The Qt6Initer registers the class into the glarea QML module, so the QML
 * files import it under its own class name.
 */
class GLTriangleItem : public QQuickFramebufferObject
{
  Q_OBJECT

 public:
  explicit GLTriangleItem(QQuickItem* parent = nullptr);
  ~GLTriangleItem() override;

  /**
   * @brief Creates the renderer that owns the GL resources and draws the
   * frames. Called by the Qt Quick render thread, which also becomes the
   * owner of the returned instance.
   *
   * @return The newly created renderer of this item.
   */
  Renderer* createRenderer() const override;
};

}  // namespace Qt6i::gl_area

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLEITEM_CLASS_H
