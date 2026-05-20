#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace wxwi
{

/**
 * @brief The root wxWidgets initialization and starter class.
 *
 * Validates the application context and launches the wxWidgets application.
 * The actual native launch is delegated to the launch() seam so the
 * orchestration may be exercised by the tests without a GUI.
 */
class WxWidgetsIniter
{
 public:
  virtual ~WxWidgetsIniter() = default;
  WxWidgetsIniter() = default;

  /**
   * @brief Starts the wxWidgets application.
   *
   * @param nactx The application context with the command line arguments.
   *
   * @return Returns the application return status. Zero at success and a
   * non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 protected:
  /**
   * @brief Launches the native wxWidgets event loop. Overridden by the tests.
   */
  virtual int launch(int& argc, char**& argv);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace wxwi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H
