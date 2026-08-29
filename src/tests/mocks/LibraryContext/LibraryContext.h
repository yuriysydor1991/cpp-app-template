#ifndef CPP_APP_TEMPLATE_011_LIBRARYCONTEXT_CLASS_H
#define CPP_APP_TEMPLATE_011_LIBRARYCONTEXT_CLASS_H

#include <gmock/gmock.h>

namespace CppAppTemplate011
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

}  // namespace CppAppTemplate011

#endif  // CPP_APP_TEMPLATE_011_LIBRARYCONTEXT_CLASS_H
