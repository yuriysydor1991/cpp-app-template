#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <vector>

namespace whisperi
{

class Microphone
{
 public:
  using samples = std::vector<float>;
  using MicrophonePtr = std::shared_ptr<Microphone>;

  virtual ~Microphone() = default;

  Microphone()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, open(_)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(Microphone&)> onMockCreate;

  MOCK_METHOD(bool, open, (int sampleRate));
  MOCK_METHOD(samples, read, ());

  inline static MicrophonePtr create()
  {
    return std::make_shared<::testing::NiceMock<Microphone>>();
  }
};

using MicrophonePtr = Microphone::MicrophonePtr;

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
