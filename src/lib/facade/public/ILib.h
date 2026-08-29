#ifndef CPP_APP_TEMPLATE_011_ILIB_CLASS_H
#define CPP_APP_TEMPLATE_011_ILIB_CLASS_H

#include <memory>

#include "LibraryAPI.h"
#include "LibraryContext.h"

/**
 * @brief The implementation part of the application library.
 * Hides all the guts of particular implementation code.
 */
namespace CppAppTemplate011
{

/**
 * @brief An abstract class to define an interface for the libraries
 * implementation variants. Introduce new methods and fields to
 * extend library functionality.
 *
 * Currently contains only simple dummy method for the demonstration purposes.
 *
 * Current file is a target for the library header installation.
 */
class TEMPLATE_LIB_API ILib
{
 public:
  using ILibPtr = std::shared_ptr<ILib>;

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
  virtual bool libcall(LibraryContextPtr ctx) = 0;
};

using ILibPtr = ILib::ILibPtr;

}  // namespace CppAppTemplate011

#endif  // CPP_APP_TEMPLATE_011_ILIB_CLASS_H
