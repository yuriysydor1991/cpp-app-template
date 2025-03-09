#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

/**
 * @brief The namespace to contain all the entities for
 * the application general purpose classes.
 */
namespace app
{

/**
 * @brief Class interface to be implemented by all available applications.
 * For example the main binary application which contains the main
 * implementation or application to print help message etc.
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
   *
   * @return Implementors should return a zero value in case of success and
   * non-zero value in case of any error.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) = 0;

  /// @brief Commonly used return status in case of any app error.
  inline static constexpr const int INVALID = 1;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IAPPLICATION_CLASS_H
