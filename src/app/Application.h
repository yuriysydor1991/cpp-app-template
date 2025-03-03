#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H

#include <memory>

#include "src/app/IApplication.h"

namespace app {

/**
 * @brief The default application implementation should be placed into
 * into current class.
 */
class Application:
  public IApplication
{
public:

  virtual int run(std::shared_ptr<ApplicationContext> ctx) override ;
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
