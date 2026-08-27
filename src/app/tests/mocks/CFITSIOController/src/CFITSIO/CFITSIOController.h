#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>

#include "src/CFITSIO/CFITSIOContext.h"

namespace cfitsioi
{

class CFITSIOController
{
 public:
  using context = CFITSIOContextPtr;
  using CFITSIOControllerPtr = std::shared_ptr<CFITSIOController>;

  virtual ~CFITSIOController() = default;

  CFITSIOController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, read(_)).WillByDefault(Return(true));
    ON_CALL(*this, write(_)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(CFITSIOController&)> onMockCreate;

  MOCK_METHOD(bool, read, (const context& ctx));
  MOCK_METHOD(bool, write, (const context& ctx));
  MOCK_METHOD(int, last_status, (), (const));
  MOCK_METHOD(std::string, last_error, (), (const));

  inline static CFITSIOControllerPtr create()
  {
    return std::make_shared<CFITSIOController>();
  }
};

using CFITSIOControllerPtr = CFITSIOController::CFITSIOControllerPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
