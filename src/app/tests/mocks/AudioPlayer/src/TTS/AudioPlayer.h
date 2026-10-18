#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/TTS/Speech.h"

namespace tts
{

class AudioPlayer
{
 public:
  using AudioPlayerPtr = std::shared_ptr<AudioPlayer>;
  using stop_check = std::function<bool()>;

  virtual ~AudioPlayer() = default;

  AudioPlayer()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, play(_, _)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(AudioPlayer&)> onMockCreate;

  MOCK_METHOD(bool, play, (const Speech& speech, const stop_check& stopped));

  inline static AudioPlayerPtr create()
  {
    return std::make_shared<::testing::NiceMock<AudioPlayer>>();
  }
};

using AudioPlayerPtr = AudioPlayer::AudioPlayerPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H
