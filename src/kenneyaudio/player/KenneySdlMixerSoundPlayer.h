#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSDLMIXERSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSDLMIXERSOUNDPLAYER_CLASS_H

#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/player/IKenneySoundPlayer.h"

namespace kenneyaudio
{

/**
 * @brief The sound player built upon the SDL2 audio subsystem and the
 * SDL_mixer decoders.
 *
 * SDL2 itself decodes the RIFF/WAVE files alone, so the compressed formats -
 * the .ogg files the Kenney packs ship among them - come from the SDL_mixer
 * satellite library. Which of it's decoders the library at hand really carries
 * is a build decision of that library, hence the extensions answered for are
 * the ones it really brought up rather than a hand written list.
 */
class KenneySdlMixerSoundPlayer : public IKenneySoundPlayer
{
 public:
  /**
   * @brief Brings the SDL2 audio subsystem, the SDL_mixer decoders and the
   * mixing device up.
   */
  KenneySdlMixerSoundPlayer();

  /**
   * @brief Takes them all back down.
   */
  ~KenneySdlMixerSoundPlayer() override;

  bool supports(const std::string& extension) const override;

  bool play(const KenneySoundPtr& sound) override;

  static IKenneySoundPlayerPtr create();

 private:
  /// @brief The sample count a single mixing step works on.
  static constexpr int CHUNK_SAMPLES = 2048;

  /// @brief The pause between the two channel checks while the sound plays.
  static constexpr int DRAIN_STEP_MS = 10;

  /// @brief The longest a single sound is waited for, so a stalled audio
  /// device ends the call instead of hanging the caller forever.
  static constexpr int DRAIN_LIMIT_MS = 30000;

  /// @brief The Mix_Init flags of the decoders really brought up.
  int mdecoders{0};

  bool minitialized{false};
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSDLMIXERSOUNDPLAYER_CLASS_H
