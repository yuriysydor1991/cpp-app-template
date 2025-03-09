#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"

namespace app
{

/**
 * @brief A help message printer application class.
 */
class ApplicationHelpPrinter : public IApplication
{
 public:
  virtual ~ApplicationHelpPrinter() = default;
  ApplicationHelpPrinter() = default;

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

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
