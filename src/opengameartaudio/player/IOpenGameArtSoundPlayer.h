#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTSOUNDPLAYER_CLASS_H

#include <memory>
#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"

namespace opengameartaudio
{

/**
 * @brief The player of a single sound of the packs made available.
 *
 * Every descendant answers for one audio backend, so the packs stay reachable
 * through the very same calls no matter which library the application links.
 */
class IOpenGameArtSoundPlayer
{
 public:
  using IOpenGameArtSoundPlayerPtr = std::shared_ptr<IOpenGameArtSoundPlayer>;

  virtual ~IOpenGameArtSoundPlayer() = default;

  /**
   * @brief Tells if the backend decodes the sound files of the given
   * extension.
   *
   * @param extension The sound file extension with no leading dot, the "wav"
   * one for example.
   *
   * @return Returns true when a sound of such a file is playable.
   */
  virtual bool supports(const std::string& extension) const = 0;

  /**
   * @brief Plays the given sound and returns once it has been played to the
   * end.
   *
   * @param sound The sound of interest.
   *
   * @return Returns true when the whole sound reached the audio device.
   */
  virtual bool play(const OpenGameArtSoundPtr& sound) = 0;
};

using IOpenGameArtSoundPlayerPtr =
    IOpenGameArtSoundPlayer::IOpenGameArtSoundPlayerPtr;

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTSOUNDPLAYER_CLASS_H
