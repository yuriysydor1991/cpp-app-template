#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H

#include <memory>

#include "ILib.h"
#include "LibraryContext.h"
#include "project-lib-decls.h"

namespace TEMPLATE_LIB_IMPL_NAMESPACE
{

/**
 * @brief The default template project library implementation class.
 * Class is designed to hold the main library implementation code. So, put
 * a new code inside of a current class' libcall method.
 */
class LibMain : public TEMPLATE_LIB_NAMESPACE::ILib
{
 public:
  using LibMainPtr = std::shared_ptr<LibMain>;
  using LibraryContextPtr = TEMPLATE_LIB_NAMESPACE::LibraryContextPtr;

  ~LibMain() override = default;
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
  virtual bool libcall(LibraryContextPtr ctx) override;

  static LibMainPtr create();
};

using LibMainPtr = LibMain::LibMainPtr;

}  // namespace TEMPLATE_LIB_IMPL_NAMESPACE

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
