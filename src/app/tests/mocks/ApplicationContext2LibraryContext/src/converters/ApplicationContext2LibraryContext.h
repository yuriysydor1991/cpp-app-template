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
  using LibraryContext = templatelib0::LibraryContext;
  using ApplicationContext = app::ApplicationContext;

  virtual ~ApplicationContext2LibraryContextSynthParent() = default;
  ApplicationContext2LibraryContextSynthParent() = default;

  virtual bool convert(std::shared_ptr<ApplicationContext> appctx,
                       std::shared_ptr<LibraryContext> libctx) = 0;
};

class ApplicationContext2LibraryContext
{
 public:
  using LibraryContext = templatelib0::LibraryContext;
  using ApplicationContext = app::ApplicationContext;

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
              (std::shared_ptr<ApplicationContext> appctx,
               std::shared_ptr<LibraryContext> libctx));
};

}  // namespace converters

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT2LIBRARYCONTEXT_CLASS_H
