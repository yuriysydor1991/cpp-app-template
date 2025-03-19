#include "src/freeglut/FreeGlutIniter.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>

namespace templateFreeGlut
{

namespace
{
constexpr const unsigned int W_DEFAULT_WIDTH = 650;
constexpr const unsigned int W_DEFAULT_HEIGHT = 200;

int current_width{0};
int current_height{0};
}  // namespace

void FreeGlutIniter::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glTranslatef(static_cast<float>(-current_width) / 2.f, 0, 0);

  glScalef(0.2f, 0.2f, 0.f);

  static const char* const implStr =
      "Your FreeGlut OpenGL scene draw goes here!";

  glutStrokeString(GLUT_STROKE_ROMAN,
                   reinterpret_cast<const unsigned char*>(implStr));

  glPopMatrix();
  glutSwapBuffers();
}

void FreeGlutIniter::init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
}

int FreeGlutIniter::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  glutInit(&ctx->argc, ctx->argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);
  glutCreateWindow(ctx->argv[0]);

  init();

  glutDisplayFunc(&FreeGlutIniter::display);
  glutReshapeFunc(&FreeGlutIniter::reshape);

  glutMainLoop();

  return 0;
}

void FreeGlutIniter::reshape(int w, int h)
{
  current_width = w;
  current_height = h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glOrtho(-static_cast<float>(w) / 2.f, static_cast<float>(w) / 2.f,
          -static_cast<float>(h) / 2.f, static_cast<float>(h) / 2.f, -1.0,
          100.0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
}

}  // namespace templateFreeGlut
