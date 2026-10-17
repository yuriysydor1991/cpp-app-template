#include "src/qt6/gl-area/GLTriangleRenderer.h"

#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QSurfaceFormat>

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

// The GLSL 1.10 / GLSL ES 1.00 sources of the compatibility and the ES
// contexts, which Qt prefixes with the matching precision defines.
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

// The GLSL 1.50 sources of the core profile contexts, which refuse the
// attribute / varying / gl_FragColor forms above.
constexpr const char* CORE_VERTEX_SHADER = R"GLSL(#version 150 core
in vec2 vertexPosition;
in vec3 vertexColour;

out vec3 cornerColour;

void main()
{
  cornerColour = vertexColour;
  gl_Position = vec4(vertexPosition, 0.0, 1.0);
}
)GLSL";

constexpr const char* CORE_FRAGMENT_SHADER = R"GLSL(#version 150 core
in vec3 cornerColour;

out vec4 fragmentColour;

void main()
{
  fragmentColour = vec4(cornerColour, 1.0);
}
)GLSL";

/** @brief Tells whether the current context is a core profile one. */
bool core_profile_context()
{
  const QOpenGLContext* const context = QOpenGLContext::currentContext();

  return context != nullptr && !context->isOpenGLES() &&
         context->format().profile() == QSurfaceFormat::CoreProfile;
}

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

  const bool core = core_profile_context();

  if (!program->addShaderFromSourceCode(
          QOpenGLShader::Vertex, core ? CORE_VERTEX_SHADER : VERTEX_SHADER) ||
      !program->addShaderFromSourceCode(
          QOpenGLShader::Fragment,
          core ? CORE_FRAGMENT_SHADER : FRAGMENT_SHADER) ||
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

  LOGI("The QQuickFramebufferObject OpenGL renderer is ready ("
       << (core ? "core profile" : "compatibility or ES") << " shaders)");

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
