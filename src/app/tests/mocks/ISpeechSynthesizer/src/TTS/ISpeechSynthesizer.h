#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "src/TTS/Speech.h"

namespace tts
{

class ISpeechSynthesizer
{
 public:
  using result = std::optional<Speech>;
  using ISpeechSynthesizerPtr = std::shared_ptr<ISpeechSynthesizer>;

  virtual ~ISpeechSynthesizer() = default;

  ISpeechSynthesizer()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, synthesize(_, _))
        .WillByDefault(Return(result{Speech{{1, 2, 3}, SAMPLE_RATE}}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(ISpeechSynthesizer&)> onMockCreate;

  inline static constexpr const int SAMPLE_RATE = 22050;

  MOCK_METHOD(result, synthesize,
              (const std::string& text, const std::string& voice));

  inline static ISpeechSynthesizerPtr create()
  {
    return std::make_shared<::testing::NiceMock<ISpeechSynthesizer>>();
  }
};

using ISpeechSynthesizerPtr = ISpeechSynthesizer::ISpeechSynthesizerPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H
