#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H

#include <memory>

#include "src/app/IApplication.h"

namespace app {

/**
 * @brief A help message printer application class.
 */
class ApplicationHelpPrinter:
  public IApplication
{
public:
  virtual ~ApplicationHelpPrinter() = default;
  ApplicationHelpPrinter() = default ;

  virtual int run(std::shared_ptr<ApplicationContext> ctx) override ;
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONHELPPRINTER_CLASS_H
