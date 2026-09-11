#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDSCONTROLLER_CLASS_H

#include <memory>

#include "src/kenneyaudio/KenneySound.h"

namespace kenneyaudio
{

/**
 * @brief The sounds of the packs, ready to be drawn and heard.
 *
 * Keeps the backend of the build together with the set it plays from, so the
 * calling code asks for a sound and plays it without knowing which audio
 * library - if any at all - ended up inside the binary and which file formats
 * that library really decodes.
 */
class IKenneySoundsController
{
 public:
  using IKenneySoundsControllerPtr = std::shared_ptr<IKenneySoundsController>;

  virtual ~IKenneySoundsController() = default;

  /**
   * @brief Tells if the project carries a backend able to play a sound.
   *
   * @return Returns false when the packs are reachable but nothing can sound
   * them.
   */
  virtual bool playable() const = 0;

  /**
   * @brief Draws a sound to play out of the whole available set.
   *
   * The sounds the backend in use really decodes come first, so the draw is
   * playable whenever the packs carry such a sound at all. It falls back to
   * any sound of the set otherwise, which keeps the drawn one worth showing
   * even where nothing can play it.
   *
   * @return Returns the drawn sound or a nullptr one for an empty set.
   */
  virtual KenneySoundPtr draw() = 0;

  /**
   * @brief Plays the given sound and returns once it has been played to the
   * end.
   *
   * @param sound The sound of interest.
   *
   * @return Returns true when the whole sound reached the audio device, false
   * with no backend built in or with a file format it misses.
   */
  virtual bool play(const KenneySoundPtr& sound) = 0;
};

using IKenneySoundsControllerPtr =
    IKenneySoundsController::IKenneySoundsControllerPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDSCONTROLLER_CLASS_H
