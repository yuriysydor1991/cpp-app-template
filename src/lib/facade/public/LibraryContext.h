#ifndef CPP_APP_TEMPLATE_012_LIBRARYCONTEXT_CLASS_H
#define CPP_APP_TEMPLATE_012_LIBRARYCONTEXT_CLASS_H

#include <memory>

#include "LibraryAPI.h"

/**
 * @brief The facade interface namespace for the library.
 * Designed to give access to the library functionality.
 *
 * The name carries the project name and the major and minor version numbers of
 * the library, so that an application may depend on many libraries derived
 * from this template - and on many versions of one of them - at once. Rename it
 * by hand in every public header and in every implementation source which names
 * it, together with the include guards above.
 */
namespace CppAppTemplate012
{

/**
 * @brief The library context class designed to pass data to
 * the library underlying implementation.
 *
 * Introduce some necessary fields for the particular newly
 * introduced code.
 *
 * Current file is a target for the library header installation.
 */
class TEMPLATE_LIB_API LibraryContext
{
 public:
  using LibraryContextPtr = std::shared_ptr<LibraryContext>;

  virtual ~LibraryContext() = default;
  LibraryContext() = default;

  // Introduce here the library required data fields.
  // Add some fields to pass data from it's users.
};

using LibraryContextPtr = LibraryContext::LibraryContextPtr;

}  // namespace CppAppTemplate012

#endif  // CPP_APP_TEMPLATE_012_LIBRARYCONTEXT_CLASS_H
