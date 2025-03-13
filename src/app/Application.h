#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H

#include <memory>

#include "LibraryContext.h"
#include "LibraryFacade.h"
#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"
#include "src/converters/ApplicationContext2LibraryContext.h"

namespace app
{

/**
 * @brief The default application implementation should be placed into
 * into current class.
 */
class Application : public IApplication
{
 public:
  virtual ~Application() = default;
  Application() = default;

  /**
   * @brief Implemented default application. See IApplication interface.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the application return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<ApplicationContext> ctx) override;

 protected:
  std::shared_ptr<templatelib0::LibraryFacade> create_lib_instance();
  std::shared_ptr<converters::ApplicationContext2LibraryContext>
  create_ctx_converter();
  std::shared_ptr<templatelib0::LibraryContext>
  create_and_convert_libctx(
      std::shared_ptr<templatelib0::LibraryFacade> libfacade,
      std::shared_ptr<ApplicationContext> ctx);
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
