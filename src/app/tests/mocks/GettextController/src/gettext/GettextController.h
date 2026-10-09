#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>

namespace gettexti
{

class GettextController
{
 public:
  using GettextControllerPtr = std::shared_ptr<GettextController>;

  virtual ~GettextController() = default;

  GettextController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, bind(_, _)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(GettextController&)> onMockCreate;

  MOCK_METHOD(bool, init, (const std::string& execPath));
  MOCK_METHOD(bool, bind,
              (const std::string& domain, const std::string& localeDir));

  inline static GettextControllerPtr create()
  {
    return std::make_shared<::testing::NiceMock<GettextController>>();
  }
};

using GettextControllerPtr = GettextController::GettextControllerPtr;

}  // namespace gettexti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H
