#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H

namespace templateSDL3
{

class OpenGLIniter
{
 public:
  virtual ~OpenGLIniter() = default;

  /**
   * @brief Requests the OpenGL 3.3 core profile context. The attributes
   * affect only the windows and the contexts created afterwards, so call it
   * after the SDL3 video subsystem init and before the window creation.
   *
   * @return Returns true on the success and false if any attribute is
   * rejected (e.g. no SDL3 video subsystem initialized).
   */
  virtual bool init_opengl();

 private:
  inline static constexpr const int GL_CONTEXT_MAJOR_VERSION = 3;
  inline static constexpr const int GL_CONTEXT_MINOR_VERSION = 3;
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
