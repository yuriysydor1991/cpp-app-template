#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACKS_CLASS_H

#include <cstddef>
#include <string>

#include "src/opengameartaudio/packs/IOpenGameArtPack.h"
#include "src/opengameartaudio/packs/IOpenGameArtPacks.h"

namespace opengameartaudio
{

/**
 * @brief The packs of the generated index.
 *
 * Builds it's set out of the OpenGameArtGeneratedSounds index alone, so it
 * carries exactly the packs the project has been configured with and reaches no
 * directory at the run time.
 */
class OpenGameArtPacks : public IOpenGameArtPacks
{
 public:
  OpenGameArtPacks();

  const PacksList& all() const override;

  IOpenGameArtPackPtr find(const std::string& packName) const override;

  std::size_t count() const override;

  static IOpenGameArtPacksPtr create();

 private:
  PacksList mpacks;
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACKS_CLASS_H
