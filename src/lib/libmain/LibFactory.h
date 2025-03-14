#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H

#include <memory>

#include "src/lib/facade/ILib.h"
#include "src/lib/facade/LibraryContext.h"

namespace lib0impl
{

/**
 * The library main factory to operate with the implementation.
 * Create appropriate instances in accordance of provided data
 * by the given context or by simply calling appropriate method.
 */
class LibFactory
{
 public:
  using ILib = templatelib0::ILib;
  using LibraryContext = ILib::LibraryContext;

  virtual ~LibFactory() = default;
  LibFactory() = default;

  /**
   * @brief Creates the default library implementation. May be overriden
   * in descendants.
   *
   * @return Returns the default library implementation. Currently returns
   * the LibMain class instance.
   */
  virtual std::shared_ptr<ILib> create_default_lib();

  /**
   * @brief Creates the default context to use in libraries implementation
   * in order to provide all necessary data.
   *
   * @return Returns empty library context instance.
   */
  virtual std::shared_ptr<LibraryContext> create_default_context();

  /**
   * @brief Creates appropriate library implementation instance
   * with accordance of provided data in the given context.
   *
   * @return Returns the appropriate library implementation if any
   * or a nullptr in case of any error. Currently returns the LibMain class
   * instance only.
   */
  virtual std::shared_ptr<ILib> create_appropriate_lib(
      std::shared_ptr<LibraryContext> ctx);

  static std::shared_ptr<LibFactory> create_factory();
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
