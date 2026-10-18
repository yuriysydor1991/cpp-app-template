#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>

#include "src/TTS/Speech.h"

namespace tts
{

class WavWriter
{
 public:
  using WavWriterPtr = std::shared_ptr<WavWriter>;

  virtual ~WavWriter() = default;

  WavWriter()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, write(_, _)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(WavWriter&)> onMockCreate;

  MOCK_METHOD(bool, write, (const Speech& speech, const std::string& path));

  inline static WavWriterPtr create()
  {
    return std::make_shared<::testing::NiceMock<WavWriter>>();
  }
};

using WavWriterPtr = WavWriter::WavWriterPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H
