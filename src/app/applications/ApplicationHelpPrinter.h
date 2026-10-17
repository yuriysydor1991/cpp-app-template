#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/applications/IApplication.h"

namespace app
{

/**
 * @brief A help message printer application class.
 */
class ApplicationHelpPrinter : public IApplication
{
 public:
  ~ApplicationHelpPrinter() override = default;
  ApplicationHelpPrinter() = default;

  /**
   * @brief Implemented default application. See IApplication interface.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * The command line errors of the context, if any, are printed into the
   * stderr stream in front of the help message.
   *
   * @return Returns the application return status. A zero value on the success
   * and other value otherwise, the help message printed because of the
   * command line errors of the context included.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) override;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
