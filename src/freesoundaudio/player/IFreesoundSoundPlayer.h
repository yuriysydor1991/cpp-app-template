#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDPLAYER_CLASS_H

#include <memory>
#include <string>

#include "src/freesoundaudio/FreesoundSound.h"

namespace freesoundaudio
{

/**
 * @brief The player of a single sound of the categories made available.
 *
 * Every descendant answers for one audio backend, so the categories stay
 * reachable through the very same calls no matter which library the application
 * links.
 */
class IFreesoundSoundPlayer
{
 public:
  using IFreesoundSoundPlayerPtr = std::shared_ptr<IFreesoundSoundPlayer>;

  virtual ~IFreesoundSoundPlayer() = default;

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
  virtual bool play(const FreesoundSoundPtr& sound) = 0;
};

using IFreesoundSoundPlayerPtr =
    IFreesoundSoundPlayer::IFreesoundSoundPlayerPtr;

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDPLAYER_CLASS_H
