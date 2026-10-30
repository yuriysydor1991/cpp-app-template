#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <vector>

namespace stt
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
  }

  MOCK_METHOD(bool, open, (int sampleRate));
  MOCK_METHOD(samples, read, ());

  inline static MicrophonePtr create()
  {
    return std::make_shared<::testing::NiceMock<Microphone>>();
  }
};

using MicrophonePtr = Microphone::MicrophonePtr;

}  // namespace stt

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
