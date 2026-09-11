#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSDLSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSDLSOUNDPLAYER_CLASS_H

#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"

namespace freesoundaudio
{

/**
 * @brief The sound player built upon the SDL2 audio subsystem.
 *
 * SDL2 itself decodes the RIFF/WAVE files alone - the compressed formats are
 * the business of the separate SDL_mixer library - so the player answers for
 * the "wav" extension and refuses the rest instead of handing a corrupted
 * buffer over to the audio device.
 */
class FreesoundSdlSoundPlayer : public IFreesoundSoundPlayer
{
 public:
  /**
   * @brief Brings the SDL2 audio subsystem up.
   */
  FreesoundSdlSoundPlayer();

  /**
   * @brief Takes the SDL2 audio subsystem back down.
   */
  ~FreesoundSdlSoundPlayer() override;

  bool supports(const std::string& extension) const override;

  bool play(const FreesoundSoundPtr& sound) override;

  static IFreesoundSoundPlayerPtr create();

 private:
  /// @brief The only sound file format the bare SDL2 decodes.
  inline static const std::string SUPPORTED_EXTENSION = "wav";

  /// @brief The pause between the two queue checks while the sound plays.
  static constexpr int DRAIN_STEP_MS = 10;

  /// @brief The longest a single sound is waited for, so a stalled audio
  /// device ends the call instead of hanging the caller forever.
  static constexpr int DRAIN_LIMIT_MS = 30000;

  bool minitialized{false};
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSDLSOUNDPLAYER_CLASS_H
