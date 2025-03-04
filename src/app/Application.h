#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H

#include <memory>

#include "src/app/IApplication.h"
#include "src/app/ApplicationContext.h"

namespace app {

/**
 * @brief The default application implementation should be placed into
 * into current class.
 */
class Application:
  public IApplication
{
public:

  /**
   * @brief Implemented default application. See IApplication interface.
   * 
   * @param ctx Application's run context with command line parameters etc.
   * 
   * @return Returns the application return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) override ;
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
