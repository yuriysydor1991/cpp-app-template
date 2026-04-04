#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H

#include <memory>
#include <gmock/gmock.h>

#include "src/app/ApplicationContext.h"

namespace plploti
{

class PLplotController
{
 public:
  using PLplotControllerPtr = std::shared_ptr<PLplotController>;

  virtual ~PLplotController() = default;
  PLplotController() = default;

  MOCK_METHOD(bool, run, (std::shared_ptr<app::ApplicationContext> ctx));

  using createMockType = testing::MockFunction<PLplotControllerPtr()>;
  inline static std::shared_ptr<createMockType> createMock;

  inline static PLplotControllerPtr create() {
    return createMock != nullptr ? createMock->AsStdFunction()() : PLplotControllerPtr{};
  }
};

using PLplotControllerPtr = PLplotController::PLplotControllerPtr;

}  // namespace plploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H
