#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACKS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/kenneyaudio/packs/IKenneyPack.h"

namespace kenneyaudio
{

/**
 * @brief Every Kenney sound pack the project has been configured with.
 */
class IKenneyPacks
{
 public:
  using IKenneyPacksPtr = std::shared_ptr<IKenneyPacks>;
  using PacksList = std::vector<IKenneyPackPtr>;

  virtual ~IKenneyPacks() = default;

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
  virtual IKenneyPackPtr find(const std::string& packName) const = 0;

  /**
   * @brief Gives the count of the available packs.
   */
  virtual std::size_t count() const = 0;
};

using IKenneyPacksPtr = IKenneyPacks::IKenneyPacksPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACKS_CLASS_H
