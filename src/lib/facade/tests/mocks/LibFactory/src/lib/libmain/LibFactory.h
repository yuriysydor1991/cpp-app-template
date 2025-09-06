#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <set>

#include "ILib.h"
#include "LibraryContext.h"

namespace lib0impl
{

class LibFactorySynthParent
{
 public:
  using ILibPtr = templatelib0::ILibPtr;
  using LibraryContextPtr = templatelib0::LibraryContextPtr;
  using LibraryContext = templatelib0::LibraryContext;

  virtual ~LibFactorySynthParent() = default;
  LibFactorySynthParent() = default;

  virtual ILibPtr create_default_lib() = 0;
  virtual LibraryContextPtr create_default_context() = 0;
  virtual ILibPtr create_appropriate_lib(LibraryContextPtr ctx) = 0;
};

class LibFactory : public LibFactorySynthParent
{
 public:
  using LibFactoryPtr = std::shared_ptr<LibFactory>;

  virtual ~LibFactory() = default;
  LibFactory()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(LibFactory& instance)> onMockCreate;

  MOCK_METHOD(ILibPtr, create_default_lib, (), (override));
  MOCK_METHOD(LibraryContextPtr, create_default_context, (), (override));
  MOCK_METHOD(ILibPtr, create_appropriate_lib, (LibraryContextPtr ctx),
              (override));

  inline static LibFactoryPtr create_factory()
  {
    return std::make_shared<LibFactory>();
  }
};

using LibFactoryPtr = LibFactory::LibFactoryPtr;

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
