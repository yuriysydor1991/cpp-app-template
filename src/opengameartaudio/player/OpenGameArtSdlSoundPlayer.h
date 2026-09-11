#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSDLSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSDLSOUNDPLAYER_CLASS_H

#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"

namespace opengameartaudio
{

/**
 * @brief The sound player built upon the SDL2 audio subsystem.
 *
 * SDL2 itself decodes the RIFF/WAVE files alone - the compressed formats are
 * the business of the separate SDL_mixer library - so the player answers for
 * the "wav" extension and refuses the rest instead of handing a corrupted
 * buffer over to the audio device.
 */
class OpenGameArtSdlSoundPlayer : public IOpenGameArtSoundPlayer
{
 public:
  /**
   * @brief Brings the SDL2 audio subsystem up.
   */
  OpenGameArtSdlSoundPlayer();

  /**
   * @brief Takes the SDL2 audio subsystem back down.
   */
  ~OpenGameArtSdlSoundPlayer() override;

  bool supports(const std::string& extension) const override;

  bool play(const OpenGameArtSoundPtr& sound) override;

  static IOpenGameArtSoundPlayerPtr create();

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

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSDLSOUNDPLAYER_CLASS_H
