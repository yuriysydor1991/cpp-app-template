#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACKS_CLASS_H

#include <cstddef>
#include <string>

#include "src/kenneyaudio/packs/IKenneyPack.h"
#include "src/kenneyaudio/packs/IKenneyPacks.h"

namespace kenneyaudio
{

/**
 * @brief The packs of the generated index.
 *
 * Builds it's set out of the KenneyGeneratedSounds index alone, so it carries
 * exactly the packs the project has been configured with and reaches no
 * directory at the run time.
 */
class KenneyPacks : public IKenneyPacks
{
 public:
  KenneyPacks();

  const PacksList& all() const override;

  IKenneyPackPtr find(const std::string& packName) const override;

  std::size_t count() const override;

  static IKenneyPacksPtr create();

 private:
  PacksList mpacks;
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACKS_CLASS_H
