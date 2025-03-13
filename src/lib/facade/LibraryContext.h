#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H

/**
 * @brief The facade interface namespace for the library.
 * Designed to give access to the library functionality.
 */
namespace templatelib
{

/**
 * @brief The library context class designed to pass data to
 * the library underlying implementation.
 *
 * Introduce some necessary fields for the particular newly
 * introduced code.
 */
class LibraryContext
{
 public:
  ~LibraryContext() = default;
  LibraryContext() = default;

  // Introduce here the library required data fields.
  // Add some fields to pass data from it's users.
};

}  // namespace templatelib

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H
