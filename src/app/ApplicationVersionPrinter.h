#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONVERSIONPRINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONVERSIONPRINTER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"

namespace app
{

/**
 * @brief A version message printer application class.
 */
class ApplicationVersionPrinter : public IApplication
{
 public:
  virtual ~ApplicationVersionPrinter() = default;
  ApplicationVersionPrinter() = default;

  /**
   * @brief Implemented default application. See IApplication interface.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the application return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) override;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONVERSIONPRINTER_CLASS_H
