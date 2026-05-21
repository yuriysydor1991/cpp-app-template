#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace cocoa
{

/**
 * @brief The root macOS Cocoa initialization and starter class.
 *
 * Validates the application context and launches the Cocoa application. The
 * actual native launch is delegated to the launch() seam so the orchestration
 * may be exercised by the tests without AppKit and without a GUI.
 */
class CocoaIniter
{
 public:
  virtual ~CocoaIniter() = default;
  CocoaIniter() = default;

  /**
   * @brief Starts the Cocoa application.
   *
   * @param nactx The application context with the command line arguments.
   *
   * @return Returns the application return status. Zero at success and a
   * non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 protected:
  /**
   * @brief Launches the native Cocoa application. Overridden by the tests.
   */
  virtual int launch(int& argc, char**& argv);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace cocoa

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H
