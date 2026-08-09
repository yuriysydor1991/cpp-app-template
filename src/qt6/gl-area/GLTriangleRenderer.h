#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLERENDERER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLERENDERER_CLASS_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QQuickFramebufferObject>
#include <QSize>
#include <memory>

namespace Qt6i::gl_area
{

/**
 * @brief Draws a single coloured triangle into the framebuffer of the
 * GLTriangleItem with the raw OpenGL calls. The instance lives on and is
 * driven by the Qt Quick render thread, so every method below is called with
 * the scene graph GL context already made current.
 *
 * Allocate your own GL resources in initialize() and issue your own draw
 * commands in render() to show a real scene. Call update() on the owning item
 * (or from synchronize()) whenever a new frame has to be produced.
 */
class GLTriangleRenderer : public QQuickFramebufferObject::Renderer,
                           protected QOpenGLFunctions
{
 public:
  GLTriangleRenderer() = default;
  ~GLTriangleRenderer() override;

 protected:
  /**
   * @brief Creates the offscreen framebuffer the scene graph shows as the
   * item texture. Called on the first frame and on every item resize.
   *
   * @param size The current item size in the device pixels.
   *
   * @return The newly created framebuffer object owned by the base class.
   */
  QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;

  /** @brief Draws a single frame into the framebuffer created above. */
  void render() override;

 private:
  /**
   * @brief Builds the shader program and uploads the triangle vertices once.
   *
   * @return True when the GL resources are ready to draw with.
   */
  bool initialize();

  std::unique_ptr<QOpenGLShaderProgram> program;
  QOpenGLBuffer vertices{QOpenGLBuffer::VertexBuffer};
  QOpenGLVertexArrayObject vertexArray;
  QSize framebufferSize;
  bool initialized{false};
};

}  // namespace Qt6i::gl_area

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_GLTRIANGLERENDERER_CLASS_H
