#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "LibraryContext.h"
#include "src/app/ApplicationContext.h"

namespace converters
{

class ApplicationContext2LibraryContextSynthParent
{
 public:
  using LibraryContext = CppAppTemplate012::LibraryContext;
  using ApplicationContextPtr = app::ApplicationContextPtr;

  virtual ~ApplicationContext2LibraryContextSynthParent() = default;
  ApplicationContext2LibraryContextSynthParent() = default;

  virtual bool convert(ApplicationContextPtr appctx,
                       std::shared_ptr<LibraryContext> libctx) = 0;
};

class ApplicationContext2LibraryContext
{
 public:
  using DefaultCtxConPtr = std::shared_ptr<ApplicationContext2LibraryContext>;
  using LibraryContext = CppAppTemplate012::LibraryContext;
  using ApplicationContextPtr = app::ApplicationContextPtr;

  virtual ~ApplicationContext2LibraryContext() = default;
  ApplicationContext2LibraryContext()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(ApplicationContext2LibraryContext& instance)>
      onMockCreate;

  MOCK_METHOD(bool, convert,
              (ApplicationContextPtr appctx,
               std::shared_ptr<LibraryContext> libctx));
};

using DefaultCtxConPtr = ApplicationContext2LibraryContext::DefaultCtxConPtr;

}  // namespace converters

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H
