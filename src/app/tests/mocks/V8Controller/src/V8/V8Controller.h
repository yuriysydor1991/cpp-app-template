#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace v8i
{

class V8Controller
{
 public:
  using result = std::optional<std::string>;
  using V8ControllerPtr = std::shared_ptr<V8Controller>;

  virtual ~V8Controller() = default;

  V8Controller()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, run(_, _)).WillByDefault(Return(result{""}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(V8Controller&)> onMockCreate;

  MOCK_METHOD(bool, init, (const std::string& execPath));
  MOCK_METHOD(result, run,
              (const std::string& source, const std::string& name));

  inline static V8ControllerPtr create()
  {
    return std::make_shared<::testing::NiceMock<V8Controller>>();
  }
};

using V8ControllerPtr = V8Controller::V8ControllerPtr;

}  // namespace v8i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H
