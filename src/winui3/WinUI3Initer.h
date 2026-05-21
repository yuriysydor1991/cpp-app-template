#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace winui3
{

/**
 * @brief The root WinUI 3 initialization and starter class.
 *
 * Validates the application context and launches the WinUI 3 application. The
 * actual native launch is delegated to the launch() seam so the orchestration
 * may be exercised by the tests without the Windows App SDK and without a GUI.
 */
class WinUI3Initer
{
 public:
  virtual ~WinUI3Initer() = default;
  WinUI3Initer() = default;

  /**
   * @brief Starts the WinUI 3 application.
   *
   * @param nactx The application context with the command line arguments.
   *
   * @return Returns the application return status. Zero at success and a
   * non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 protected:
  /**
   * @brief Launches the native WinUI 3 application. Overridden by the tests.
   */
  virtual int launch(int& argc, char**& argv);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace winui3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H
