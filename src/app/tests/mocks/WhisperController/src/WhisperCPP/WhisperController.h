#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace whisperi
{

class WhisperController
{
 public:
  using result = std::optional<std::string>;
  using samples = std::vector<float>;
  using WhisperControllerPtr = std::shared_ptr<WhisperController>;

  virtual ~WhisperController() = default;

  WhisperController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_, _)).WillByDefault(Return(true));
    ON_CALL(*this, listen()).WillByDefault(Return(result{""}));
    ON_CALL(*this, transcribe(_)).WillByDefault(Return(result{""}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(WhisperController&)> onMockCreate;

  MOCK_METHOD(bool, init,
              (const std::string& modelPath, const std::string& language));
  MOCK_METHOD(result, listen, ());
  MOCK_METHOD(result, transcribe, (const samples& audio));

  inline static WhisperControllerPtr create()
  {
    return std::make_shared<::testing::NiceMock<WhisperController>>();
  }
};

using WhisperControllerPtr = WhisperController::WhisperControllerPtr;

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H
