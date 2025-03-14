#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <set>

#include "src/lib/facade/ILib.h"
#include "src/lib/facade/LibraryContext.h"

namespace lib0impl
{

class LibFactorySynthParent
{
 public:
  using ILib = templatelib0::ILib;
  using LibraryContext = ILib::LibraryContext;

  virtual ~LibFactorySynthParent() = default;
  LibFactorySynthParent() = default;

  virtual std::shared_ptr<ILib> create_default_lib() = 0;
  virtual std::shared_ptr<LibraryContext> create_default_context() = 0;
  virtual std::shared_ptr<ILib> create_appropriate_lib(
      std::shared_ptr<LibraryContext> ctx) = 0;
};

class LibFactoryRealMock : public LibFactorySynthParent
{
 public:
  virtual ~LibFactoryRealMock() = default;

  LibFactoryRealMock() = default;

  MOCK_METHOD(std::shared_ptr<ILib>, create_default_lib, (), (override));
  MOCK_METHOD(std::shared_ptr<LibraryContext>, create_default_context, (),
              (override));
  MOCK_METHOD(std::shared_ptr<ILib>, create_appropriate_lib,
              (std::shared_ptr<LibraryContext> ctx), (override));

  inline static std::shared_ptr<LibFactoryRealMock> create_factory()
  {
    return std::make_shared<LibFactoryRealMock>();
  }
};

class LibFactory : public LibFactorySynthParent
{
 public:
  virtual ~LibFactory() { available_instances.erase(this); }

  LibFactory()
  {
    recreate_real();
    available_instances.insert(this);
  }

  inline static std::set<LibFactory*> available_instances;

  virtual std::shared_ptr<ILib> create_default_lib() override
  {
    EXPECT_NE(real, nullptr);

    return real->create_default_lib();
  }

  virtual std::shared_ptr<LibraryContext> create_default_context() override
  {
    EXPECT_NE(real, nullptr);

    return real->create_default_context();
  }

  virtual std::shared_ptr<ILib> create_appropriate_lib(
      std::shared_ptr<LibraryContext> ctx) override
  {
    EXPECT_NE(real, nullptr);

    return real->create_appropriate_lib(ctx);
  }

  inline static std::shared_ptr<LibFactory> create_factory()
  {
    return std::make_shared<LibFactory>();
  }

  inline void recreate_real() { real = std::make_shared<LibFactoryRealMock>(); }

  std::shared_ptr<LibFactoryRealMock> real;

  inline LibFactoryRealMock& get_real()
  {
    EXPECT_NE(real, nullptr);

    return *real;
  }
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
