#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace pgploti
{

class PGPLOTController
{
 public:
  using PGPLOTControllerPtr = std::shared_ptr<PGPLOTController>;

  virtual ~PGPLOTController() = default;
  PGPLOTController() = default;

  MOCK_METHOD(bool, run, (std::shared_ptr<app::ApplicationContext> ctx));

  using createMockType = testing::MockFunction<PGPLOTControllerPtr()>;
  inline static std::shared_ptr<createMockType> createMock;

  inline static PGPLOTControllerPtr create()
  {
    return createMock != nullptr ? createMock->AsStdFunction()()
                                 : PGPLOTControllerPtr{};
  }
};

using PGPLOTControllerPtr = PGPLOTController::PGPLOTControllerPtr;

}  // namespace pgploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
