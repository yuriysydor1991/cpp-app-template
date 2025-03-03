#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace app {

/**
 * @brief Class interface to be implemented by all available applications.
 * For example the main binary application which contains the main implementation
 * or application to print help message etc.
 */
class IApplication
{
public:
  virtual ~IApplication() = default;
  IApplication() = default;

  /** 
   * @brief the main application routine to execute the implemented application.
   * 
   * @param ctx A filled context to pass data to the app instance.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) = 0;

protected:
  static constexpr const int INVALID = 1 ;
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H
