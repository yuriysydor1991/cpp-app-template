#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ILIB_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ILIB_CLASS_H

#include <memory>

#include "src/lib/facade/LibraryContext.h"

/**
 * @brief The implementation part of the application library.
 * Hides all the guts of particular implementation code.
 */
namespace lib0impl
{

/**
 * @brief An abstract class to define an interface for the libraries
 * implementation variants.
 */
class ILib
{
 public:
  using LibraryContext = templatelib::LibraryContext;

  virtual ~ILib() = default;
  ILib() = default;

  /**
   * @brief The library interface method which every ILib descendant
   * must to implement in order to provide it's functionality.
   *
   * @param ctx A filled LibraryContext instance with appropriate data
   * to perform particular library implementation actions.
   *
   * @return Should return a true value on the success and false
   * in case of any error.
   */
  virtual bool libcall(std::shared_ptr<LibraryContext> ctx) = 0;
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ILIB_CLASS_H
