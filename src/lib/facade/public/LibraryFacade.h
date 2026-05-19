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
  static LibraryContextPtr create_library_context();

  /**
   * @brief Creates the default library implementation.
   *
   * @return Returns the default library implementation. Currently returns
   * the LibMain class instance.
   */
  static ILibPtr create_default_lib();

  /**
   * @brief Creates and returns the appropriate ILib instance.
   *
   * @param ctx Filled LibraryContext to check for an appropriate ILib instance.
   *
   * @return Returns a new ILib descendant or a nullptr in case of any error.
   */
  static ILibPtr create_library(LibraryContextPtr ctx);
};

}  // namespace templatelib0

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
