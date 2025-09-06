#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H

#include <memory>

#include "LibraryContext.h"
#include "src/app/ApplicationContext.h"

/**
 * @brief The namespace for the Application's all converter classes.
 */
namespace converters
{

/**
 * @brief The default application implementation should be placed into
 * into current class. See the Application class default run method
 * implementation on how current class is being used.
 */
class ApplicationContext2LibraryContext
{
 public:
  using DefaultCtxConPtr = std::shared_ptr<ApplicationContext2LibraryContext>;

  using LibraryContextPtr = templatelib0::LibraryContextPtr;
  using ApplicationContext = app::ApplicationContext;

  virtual ~ApplicationContext2LibraryContext() = default;
  ApplicationContext2LibraryContext() = default;

  /**
   * @brief Transfers some data of interest from the ApplicationContext into
   * the destination LibraryContext instance in order to pass the LibraryContext
   * instance to the library routines and hence provided necessary data.
   * See the Application class default run method implementation on how it is
   * used.
   *
   * @param appctx Application's run context with command line parameters etc.
   * @param libctx The filled LibraryContext instance with transferred data for
   * the ILib instance to receive. Receiver of the data transfer.
   *
   * @return Returns a true value in case of successful data transfer and
   * a false boolean value in case of any error.
   */
  virtual bool convert(std::shared_ptr<ApplicationContext> appctx,
                       LibraryContextPtr libctx);
};

using DefaultCtxConPtr = ApplicationContext2LibraryContext::DefaultCtxConPtr;

}  // namespace converters

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H
