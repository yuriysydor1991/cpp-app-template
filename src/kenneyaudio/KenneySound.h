#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUND_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUND_CLASS_H

#include <memory>
#include <string>

#include "src/kenneyaudio/packs/IKenneyPack.h"

namespace kenneyaudio
{

/**
 * @brief A single sound file of a Kenney CC0 pack.
 *
 * Pairs a pack with the path of a sound file inside it and derives every name
 * the surrounding code asks the pair for: the plain sound name, the file name,
 * the resource alias and the absolute path of the very sound file.
 */
class KenneySound
{
 public:
  using KenneySoundPtr = std::shared_ptr<KenneySound>;

  virtual ~KenneySound() = default;

  /**
   * @brief Constructs the sound of the given pack and pack relative path.
   *
   * A pack ships it's files under a subdirectory of it's own, which differs
   * from pack to pack, so the path stays whole instead of a plain file name.
   *
   * @param gpack The pack the sound belongs to.
   * @param gpath The sound file path relative to the pack directory, the
   * "Audio/click_001.ogg" one for example.
   */
  KenneySound(IKenneyPackPtr gpack, std::string gpath);

  /**
   * @brief Gives the pack the sound belongs to.
   */
  const IKenneyPackPtr& pack() const;

  /**
   * @brief Gives the sound file path relative to the pack directory.
   *
   * @return Returns the relative path, the "Audio/click_001.ogg" one for
   * example.
   */
  const std::string& path() const;

  /**
   * @brief Gives the sound file name.
   *
   * @return Returns the file name, the "click_001.ogg" one for example.
   */
  std::string fileName() const;

  /**
   * @brief Gives the plain sound name with no path or extension parts.
   *
   * @return Returns the name, the "click_001" one for example.
   */
  std::string name() const;

  /**
   * @brief Gives the sound file extension with no leading dot.
   *
   * @return Returns the extension, the "ogg" one for example, an empty string
   * for a file carrying none.
   */
  std::string extension() const;

  /**
   * @brief Gives the alias every generated resource manifest keys the sound by.
   *
   * Both the .qrc and the .gresource.xml manifests the kenney audio enabler
   * writes carry this very alias, so it is the single name the compiled in
   * resource and the code below agree upon. It is, at the same time, the path
   * of the sound file relative to the packs root directory.
   *
   * @return Returns the alias, the "interface-sounds/Audio/click_001.ogg" one
   * for example.
   */
  std::string alias() const;

  /**
   * @brief Gives the absolute path of the sound file inside the packs
   * directory the project has been configured with.
   *
   * @return Returns the absolute path of the sound file.
   */
  std::string filePath() const;

  static KenneySoundPtr create(IKenneyPackPtr gpack, std::string gpath);

 private:
  IKenneyPackPtr mpack;
  std::string mpath;
};

using KenneySoundPtr = KenneySound::KenneySoundPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUND_CLASS_H
