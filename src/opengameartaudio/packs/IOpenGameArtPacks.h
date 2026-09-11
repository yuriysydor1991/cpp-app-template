#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACKS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/opengameartaudio/packs/IOpenGameArtPack.h"

namespace opengameartaudio
{

/**
 * @brief Every OpenGameArt sound pack the project has been configured with.
 */
class IOpenGameArtPacks
{
 public:
  using IOpenGameArtPacksPtr = std::shared_ptr<IOpenGameArtPacks>;
  using PacksList = std::vector<IOpenGameArtPackPtr>;

  virtual ~IOpenGameArtPacks() = default;

  /**
   * @brief Gives every available pack, ordered by the pack name.
   */
  virtual const PacksList& all() const = 0;

  /**
   * @brief Searches for the pack of the given name.
   *
   * @param packName The pack name of interest.
   *
   * @return Returns the pack or a nullptr one when none carries such a name.
   */
  virtual IOpenGameArtPackPtr find(const std::string& packName) const = 0;

  /**
   * @brief Gives the count of the available packs.
   */
  virtual std::size_t count() const = 0;
};

using IOpenGameArtPacksPtr = IOpenGameArtPacks::IOpenGameArtPacksPtr;

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACKS_CLASS_H
