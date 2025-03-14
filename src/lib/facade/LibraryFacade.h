#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H

#include <memory>

#include "ILib.h"
#include "LibraryContext.h"

namespace templatelib0
{

/**
 * @brief The facade interface class of the library.
 * Designed to give access to the library functionality.
 * The LibraryFacade class designed to not have changes
 * inside of it nor does not require extra code introduced.
 * Watch the LibMain which is designed to receive
 * the main implementation of the library code.
 *
 * Current file is a target for the library header installation.
 */
class LibraryFacade
{
 public:
  virtual ~LibraryFacade() = default;
  LibraryFacade() = default;

  /**
   * @brief Factory method to create empty library context for
   * the users of interest.
   *
   * @return Returns empty library context instance of the LibraryContext class.
   */
  virtual std::shared_ptr<LibraryContext> create_library_context();

  /**
   * @brief Creates and returns the appropriate ILib instance.
   *
   * @param ctx Filled LibraryContext to check for an appropriate ILib instance.
   *
   * @return Returns a new ILib descendant or a nullptr in case of any error.
   */
  virtual std::shared_ptr<ILib> create_library(
      std::shared_ptr<LibraryContext> ctx);

  /**
   * @brief An interface for the library functionality. Library may
   * behave differently in accordance with provided data in the ctx param.
   * Should be filled appropriately in order for the library function properly.
   * Creates appropriate ILib instance calls it's libcall method.
   * The ILib instance will be destructed afterwards.
   *
   * @param ctx A LibraryContext class instance filled with necessary data in
   * order for the library implementation to work properly.
   *
   * @return Returns a true value on the success and false in case of any error.
   */
  virtual bool libcall(std::shared_ptr<LibraryContext> ctx);
};

}  // namespace templatelib0

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
