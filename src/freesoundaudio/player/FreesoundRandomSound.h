#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDRANDOMSOUND_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDRANDOMSOUND_CLASS_H

#include <random>
#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"

namespace freesoundaudio
{

/**
 * @brief The picker of a single sound out of the whole available set.
 *
 * A demo playing the very same click on every run proves little, so the sound
 * to play is drawn at the run time. The seed is takeable, which is what lets a
 * test ask for a repeatable draw.
 */
class FreesoundRandomSound
{
 public:
  using Seed = std::mt19937::result_type;

  /**
   * @brief Constructs the picker seeded by the system entropy source.
   */
  FreesoundRandomSound();

  /**
   * @brief Constructs the picker seeded by the given value, so it's draws
   * repeat.
   *
   * @param gseed The seed of the draws.
   */
  explicit FreesoundRandomSound(Seed gseed);

  /**
   * @brief Draws a sound out of the whole given set.
   *
   * @param sounds The set to draw of.
   *
   * @return Returns the drawn sound or a nullptr one for an empty or a nullptr
   * set.
   */
  FreesoundSoundPtr pick(const IFreesoundSoundsPtr& sounds);

  /**
   * @brief Draws a sound of the given file extension out of the given set.
   *
   * The counterpart of a "pick whatever the player at hand really decodes"
   * call, so a backend covering a single format still gets a sound to play.
   *
   * @param sounds The set to draw of.
   * @param extension The sound file extension of interest with no leading dot.
   *
   * @return Returns the drawn sound or a nullptr one when the set carries no
   * sound of such an extension.
   */
  FreesoundSoundPtr pick(const IFreesoundSoundsPtr& sounds,
                         const std::string& extension);

 private:
  std::mt19937 mgenerator;
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDRANDOMSOUND_CLASS_H
