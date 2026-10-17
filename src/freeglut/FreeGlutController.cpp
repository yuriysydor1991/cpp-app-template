#include "src/freeglut/FreeGlutController.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cassert>
#include <memory>

#include "src/app/applications/IApplication.h"
#include "src/log/log.h"

namespace templateFreeGlut
{

namespace
{
constexpr const unsigned int W_DEFAULT_WIDTH = 650;
constexpr const unsigned int W_DEFAULT_HEIGHT = 200;

constexpr const unsigned int STOP_CHECK_PERIOD_MS = 100;

int current_width{0};
int current_height{0};

std::shared_ptr<app::ApplicationContext> runCtx;
}  // namespace

void FreeGlutController::display()
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

void FreeGlutController::init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
}

int FreeGlutController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return app::IApplication::INVALID;
  }

  runCtx = ctx;

  glutInit(&ctx->get_argc(), ctx->get_argv());
  // the window close returns from the main loop instead of the exit() call
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);
  glutCreateWindow(ctx->get_argv()[0]);

  init();

  glutDisplayFunc(&FreeGlutController::display);
  glutReshapeFunc(&FreeGlutController::reshape);
  glutTimerFunc(STOP_CHECK_PERIOD_MS, &FreeGlutController::check_stop, 0);

  glutMainLoop();

  runCtx.reset();

  return 0;
}

void FreeGlutController::check_stop([[maybe_unused]] int value)
{
  // the stop signals handlers only raise the context stop flag
  if (runCtx == nullptr || runCtx->get_stop()) {
    glutLeaveMainLoop();
    return;
  }

  glutTimerFunc(STOP_CHECK_PERIOD_MS, &FreeGlutController::check_stop, 0);
}

void FreeGlutController::reshape(int w, int h)
{
  current_width = w;
  current_height = h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glOrtho(-static_cast<double>(w) / 2.0, static_cast<double>(w) / 2.0,
          -static_cast<double>(h) / 2.0, static_cast<double>(h) / 2.0, -1.0,
          100.0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
}

}  // namespace templateFreeGlut
