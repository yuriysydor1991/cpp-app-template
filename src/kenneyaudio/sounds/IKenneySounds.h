#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/kenneyaudio/KenneySound.h"

namespace kenneyaudio
{

/**
 * @brief The whole sound set of the Kenney packs the project has been
 * configured with.
 *
 * Every sound of every configured pack is reachable here, so the application
 * code picks the ones it needs (and hands them over to the resource system of
 * it's GUI toolkit) without a single sound name written into the sources by
 * hand.
 */
class IKenneySounds
{
 public:
  using IKenneySoundsPtr = std::shared_ptr<IKenneySounds>;
  using SoundsList = std::vector<KenneySoundPtr>;

  virtual ~IKenneySounds() = default;

  /**
   * @brief Gives every sound of every pack, ordered by the pack and then by
   * the sound path.
   *
   * @return Returns the whole sound set.
   */
  virtual const SoundsList& all() const = 0;

  /**
   * @brief Gives every sound of the given pack.
   *
   * @param packName The pack name of interest, the "interface-sounds" one for
   * example.
   *
   * @return Returns the sounds of the pack, an empty list when the set carries
   * no such pack.
   */
  virtual SoundsList ofPack(const std::string& packName) const = 0;

  /**
   * @brief Searches for the sound of the given pack and pack relative path.
   *
   * @param packName The pack name of interest.
   * @param soundPath The sound file path relative to the pack directory, the
   * "Audio/click_001.ogg" one for example.
   *
   * @return Returns the sound or a nullptr one when the set carries none.
   */
  virtual KenneySoundPtr find(const std::string& packName,
                              const std::string& soundPath) const = 0;

  /**
   * @brief Gives every sound which plain name contains the given part.
   *
   * The counterpart of a "find the sounds of interest by hand" browse over the
   * packs, so no file manager and no audio player is needed to look one up.
   *
   * @param namePart The sound name part to look for, the "click" one for
   * example.
   *
   * @return Returns the matching sounds of every pack.
   */
  virtual SoundsList search(const std::string& namePart) const = 0;

  /**
   * @brief Gives the count of the sounds the whole set carries.
   */
  virtual std::size_t count() const = 0;
};

using IKenneySoundsPtr = IKenneySounds::IKenneySoundsPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYSOUNDS_CLASS_H
