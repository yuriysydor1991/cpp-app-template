#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H

#include <memory>
#include <functional>

#include <gmock/gmock.h>

#include "LibraryContext.h"

namespace templatelib
{

class LibraryFacadeSynthBaseClass
{
 public:
  virtual ~LibraryFacadeSynthBaseClass() = default;
  LibraryFacadeSynthBaseClass() = default;

  virtual std::shared_ptr<LibraryContext> create_library_context() = 0;
  virtual bool libcall(std::shared_ptr<LibraryContext> ctx) = 0;
};

class LibraryFacade: public LibraryFacadeSynthBaseClass
{
 public:
  virtual ~LibraryFacade() = default;
  LibraryFacade() {
    if (onMockCreate) { onMockCreate(*this); }
  }

  inline static std::function<void(LibraryFacade& instance)> onMockCreate;

  MOCK_METHOD(std::shared_ptr<LibraryContext>, create_library_context, ());
  MOCK_METHOD(bool, libcall, (std::shared_ptr<LibraryContext> ctx));
};

}  // namespace templatelib

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
