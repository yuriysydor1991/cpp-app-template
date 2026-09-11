#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDS_CLASS_H

#include <cstddef>
#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/packs/IKenneyPacks.h"
#include "src/kenneyaudio/sounds/IKenneySounds.h"

namespace kenneyaudio
{

/**
 * @brief The sound set of the generated index.
 *
 * Builds it's set out of the KenneyGeneratedSounds index alone, so it carries
 * exactly the sounds the project has been configured with and reaches no
 * directory at the run time.
 */
class KenneySounds : public IKenneySounds
{
 public:
  /**
   * @brief Constructs the set out of the given packs.
   *
   * @param gpacks The packs to gather the sounds of.
   */
  explicit KenneySounds(IKenneyPacksPtr gpacks);

  const SoundsList& all() const override;

  SoundsList ofPack(const std::string& packName) const override;

  KenneySoundPtr find(const std::string& packName,
                      const std::string& soundPath) const override;

  SoundsList search(const std::string& namePart) const override;

  std::size_t count() const override;

  static IKenneySoundsPtr create();

  static IKenneySoundsPtr create(IKenneyPacksPtr gpacks);

 private:
  SoundsList msounds;
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDS_CLASS_H
