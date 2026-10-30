#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace stt
{

class SpeechListener
{
 public:
  using result = std::optional<std::string>;
  using SpeechListenerPtr = std::shared_ptr<SpeechListener>;

  virtual ~SpeechListener() = default;

  SpeechListener()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, listen()).WillByDefault(Return(result{""}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(SpeechListener&)> onMockCreate;

  MOCK_METHOD(bool, init, (const std::string& model));
  MOCK_METHOD(result, listen, ());

  inline static SpeechListenerPtr create()
  {
    return std::make_shared<::testing::NiceMock<SpeechListener>>();
  }
};

using SpeechListenerPtr = SpeechListener::SpeechListenerPtr;

}  // namespace stt

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H
