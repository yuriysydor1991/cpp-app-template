#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H

#include <memory>
#include <functional>
#include <set>

#include <gmock/gmock.h>

#include "src/lib/facade/ILib.h"
#include "src/lib/facade/LibraryContext.h"

namespace lib0impl
{

class LibFactorySynthParent
{
public:
using ILib = templatelib0::ILib;
  using LibraryContext = ILib::LibraryContext;

    virtual ~LibFactorySynthParent () = default;
    LibFactorySynthParent() = default;

    virtual std::shared_ptr<ILib> create_default_lib() = 0;
    virtual std::shared_ptr<LibraryContext> create_default_context() = 0;
    virtual std::shared_ptr<ILib> create_appropriate_lib(
        std::shared_ptr<LibraryContext> ctx) = 0;
};

class LibFactory: public LibFactorySynthParent
{
 public:
  virtual ~LibFactory()
  {
    available_instances.erase(this);
  }

  LibFactory()
  {
    available_instances.insert(this);
  }

  inline static std::set<LibFactory*> available_instances;

  MOCK_METHOD(std::shared_ptr<ILib>, create_default_lib, (), (override));
  MOCK_METHOD(std::shared_ptr<LibraryContext>, create_default_context, (), (override));
  MOCK_METHOD(std::shared_ptr<ILib>, create_appropriate_lib, (
      std::shared_ptr<LibraryContext> ctx), (override));
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBFACTORY_CLASS_H
