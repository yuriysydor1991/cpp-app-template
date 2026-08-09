#include "src/qt6/gl-area/GLTriangleRenderer.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

#include "src/log/log.h"

namespace Qt6i::gl_area
{

namespace
{

/** @brief The triangle corners in the normalized device coordinates followed
 * by the RGB colour of every corner. */
constexpr GLfloat TRIANGLE[] = {
    0.0F,   0.75F,  1.0F, 0.0F, 0.0F,  //
    -0.75F, -0.75F, 0.0F, 1.0F, 0.0F,  //
    0.75F,  -0.75F, 0.0F, 0.0F, 1.0F,
};

constexpr int TRIANGLE_CORNERS = 3;
constexpr int POSITION_COMPONENTS = 2;
constexpr int COLOUR_COMPONENTS = 3;
constexpr int CORNER_STRIDE = static_cast<int>(
    (POSITION_COMPONENTS + COLOUR_COMPONENTS) * sizeof(GLfloat));
constexpr int COLOUR_OFFSET =
    static_cast<int>(POSITION_COMPONENTS * sizeof(GLfloat));

constexpr const char* POSITION_ATTRIBUTE = "vertexPosition";
constexpr const char* COLOUR_ATTRIBUTE = "vertexColour";

constexpr const char* VERTEX_SHADER = R"GLSL(
attribute highp vec2 vertexPosition;
attribute lowp vec3 vertexColour;

varying lowp vec3 cornerColour;

void main()
{
  cornerColour = vertexColour;
  gl_Position = vec4(vertexPosition, 0.0, 1.0);
}
)GLSL";

constexpr const char* FRAGMENT_SHADER = R"GLSL(
varying lowp vec3 cornerColour;

void main()
{
  gl_FragColor = vec4(cornerColour, 1.0);
}
)GLSL";

}  // namespace

GLTriangleRenderer::~GLTriangleRenderer()
{
  if (vertices.isCreated()) {
    vertices.destroy();
  }

  if (vertexArray.isCreated()) {
    vertexArray.destroy();
  }
}

QOpenGLFramebufferObject* GLTriangleRenderer::createFramebufferObject(
    const QSize& size)
{
  QOpenGLFramebufferObjectFormat format;

  format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  format.setSamples(4);

  framebufferSize = size;

  return new QOpenGLFramebufferObject(size, format);
}

bool GLTriangleRenderer::initialize()
{
  if (initialized) {
    return program != nullptr;
  }

  initialized = true;

  initializeOpenGLFunctions();

  program = std::make_unique<QOpenGLShaderProgram>();

  if (!program->addShaderFromSourceCode(QOpenGLShader::Vertex, VERTEX_SHADER) ||
      !program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        FRAGMENT_SHADER) ||
      !program->link()) {
    LOGE("Fail to build the triangle shader program: "
         << program->log().toStdString());
    program.reset();
    return false;
  }

  // The core profile contexts refuse to draw without a vertex array object,
  // while the older ones simply ignore it.
  vertexArray.create();

  QOpenGLVertexArrayObject::Binder arrayBinder{&vertexArray};

  if (!vertices.create()) {
    LOGE("Fail to create the triangle vertex buffer");
    program.reset();
    return false;
  }

  vertices.bind();
  vertices.allocate(TRIANGLE, static_cast<int>(sizeof(TRIANGLE)));
  vertices.release();

  LOGI("The QQuickFramebufferObject OpenGL renderer is ready");

  return true;
}

void GLTriangleRenderer::render()
{
  if (!initialize()) {
    return;
  }

  glViewport(0, 0, framebufferSize.width(), framebufferSize.height());

  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QOpenGLVertexArrayObject::Binder arrayBinder{&vertexArray};

  program->bind();
  vertices.bind();

  program->enableAttributeArray(POSITION_ATTRIBUTE);
  program->setAttributeBuffer(POSITION_ATTRIBUTE, GL_FLOAT, 0,
                              POSITION_COMPONENTS, CORNER_STRIDE);
  program->enableAttributeArray(COLOUR_ATTRIBUTE);
  program->setAttributeBuffer(COLOUR_ATTRIBUTE, GL_FLOAT, COLOUR_OFFSET,
                              COLOUR_COMPONENTS, CORNER_STRIDE);

  glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_CORNERS);

  program->disableAttributeArray(COLOUR_ATTRIBUTE);
  program->disableAttributeArray(POSITION_ATTRIBUTE);

  vertices.release();
  program->release();
}

}  // namespace Qt6i::gl_area
