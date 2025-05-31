#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H

#include <memory>

#include "src/lib/facade/ILib.h"
#include "src/lib/facade/LibraryContext.h"

namespace lib0impl
{

/**
 * @brief The default template project library implementation class.
 * Class is designed to hold the main library implementation code. So, put
 * a new code inside of a current class' libcall method.
 */
class LibMain : public templatelib0::ILib
{
 public:
  virtual ~LibMain() = default;
  LibMain();

  /**
   * @brief The implemented library interface method derived from an ILib
   * abstract class. Designed to contain the main library code implementation.
   *
   * @param ctx A filled LibraryContext instance with appropriate data
   * to perform it's actions.
   *
   * @return Returns a true value on the success and false in case of any error.
   */
  virtual bool libcall(std::shared_ptr<LibraryContext> ctx) override;
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
