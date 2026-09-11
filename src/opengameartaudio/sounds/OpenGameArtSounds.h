#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSOUNDS_CLASS_H

#include <cstddef>
#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/packs/IOpenGameArtPacks.h"
#include "src/opengameartaudio/sounds/IOpenGameArtSounds.h"

namespace opengameartaudio
{

/**
 * @brief The sound set of the generated index.
 *
 * Builds it's set out of the OpenGameArtGeneratedSounds index alone, so it
 * carries exactly the sounds the project has been configured with and reaches
 * no directory at the run time.
 */
class OpenGameArtSounds : public IOpenGameArtSounds
{
 public:
  /**
   * @brief Constructs the set out of the given packs.
   *
   * @param gpacks The packs to gather the sounds of.
   */
  explicit OpenGameArtSounds(IOpenGameArtPacksPtr gpacks);

  const SoundsList& all() const override;

  SoundsList ofPack(const std::string& packName) const override;

  OpenGameArtSoundPtr find(const std::string& packName,
                           const std::string& soundPath) const override;

  SoundsList search(const std::string& namePart) const override;

  std::size_t count() const override;

  static IOpenGameArtSoundsPtr create();

  static IOpenGameArtSoundsPtr create(IOpenGameArtPacksPtr gpacks);

 private:
  SoundsList msounds;
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTSOUNDS_CLASS_H
