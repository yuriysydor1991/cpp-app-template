#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDPLAYER_CLASS_H

#include <memory>
#include <string>

#include "src/kenneyaudio/KenneySound.h"

namespace kenneyaudio
{

/**
 * @brief The player of a single sound of the packs made available.
 *
 * Every descendant answers for one audio backend, so the packs stay reachable
 * through the very same calls no matter which library the application links.
 */
class IKenneySoundPlayer
{
 public:
  using IKenneySoundPlayerPtr = std::shared_ptr<IKenneySoundPlayer>;

  virtual ~IKenneySoundPlayer() = default;

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
  virtual bool play(const KenneySoundPtr& sound) = 0;
};

using IKenneySoundPlayerPtr = IKenneySoundPlayer::IKenneySoundPlayerPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDPLAYER_CLASS_H
