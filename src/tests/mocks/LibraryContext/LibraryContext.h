#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H

#include <gmock/gmock.h>

namespace templatelib0
{

class LibraryContext
{
 public:
  using LibraryContextPtr = std::shared_ptr<LibraryContext>;

  virtual ~LibraryContext() = default;
  LibraryContext() = default;

  // Introduce here the library required data fields.
  // Add some fields to pass data from it's users.
};

using LibraryContextPtr = LibraryContext::LibraryContextPtr;

}  // namespace templatelib0

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYCONTEXT_CLASS_H
