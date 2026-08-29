#ifndef CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H
#define CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H

#include <memory>

#include "ILib.h"
#include "ILogger.h"
#include "LibraryAPI.h"
#include "LibraryContext.h"

namespace CppAppTemplate012
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
class TEMPLATE_LIB_API LibraryFacade
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

  /**
   * @brief Hands the logger instance owned by the library user over to the
   * library, so every library log message lands in the very same destination
   * as the messages of the code which uses that library.
   *
   * The library carries its own copy of the logging subsystem, so without that
   * call it would create an own logger instance with an own log file. Call it
   * once, before any other library call, right after the library user
   * initializes its own logging. The application part of the current project
   * does it inside the app::ApplicationFactory::run method.
   *
   * Any logger::ILogger implementation is accepted, so an application built on
   * top of another logging library is free to hand its own wrapper over.
   *
   * @param appLogger The library user owned logger instance. If the null
   * pointer given - nothing will be performed and the library keeps its own
   * logger.
   */
  static void init_logger(const logger::ILoggerPtr& appLogger);
};

}  // namespace CppAppTemplate012

#endif  // CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H
