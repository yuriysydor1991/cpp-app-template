#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "ILib.h"
#include "LibraryContext.h"

namespace templatelib0
{

class LibraryFacade
{
 public:
  using LibraryContextPtr = templatelib0::LibraryContextPtr;

  virtual ~LibraryFacade() = default;
  LibraryFacade() = default;

  inline static testing::MockFunction<ILibPtr(LibraryContextPtr ctx)>
      create_library_mock;
  inline static testing::MockFunction<LibraryContextPtr()>
      create_library_context_mock;
  inline static testing::MockFunction<ILibPtr()> create_default_lib_mock;

  inline static ILibPtr create_library(LibraryContextPtr ctx)
  {
    return create_library_mock.AsStdFunction()(ctx);
  }
  inline static LibraryContextPtr create_library_context()
  {
    return create_library_context_mock.AsStdFunction()();
  }
  inline static ILibPtr create_default_lib()
  {
    return create_default_lib_mock.AsStdFunction()();
  }
};

}  // namespace templatelib0

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYFACADE_CLASS_H
