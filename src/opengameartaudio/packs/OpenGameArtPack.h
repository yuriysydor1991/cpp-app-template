#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACK_CLASS_H

#include <string>

#include "src/opengameartaudio/packs/IOpenGameArtPack.h"

namespace opengameartaudio
{

/**
 * @brief A OpenGameArt sound pack named at the run time.
 *
 * The packs to make available are a build option rather than a fixed set, so
 * one descendant carrying the configured name serves every pack instead of a
 * hand written class per pack.
 */
class OpenGameArtPack : public IOpenGameArtPack
{
 public:
  /**
   * @brief Constructs the pack of the given name and license.
   *
   * @param gname The pack name, the "cc0-interface-sfx" one for example.
   * @param glicense The license the pack was published under.
   */
  OpenGameArtPack(std::string gname, std::string glicense);

  std::string name() const override;

  std::string license() const override;

  static IOpenGameArtPackPtr create(std::string gname, std::string glicense);

 private:
  std::string mname;
  std::string mlicense;
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTPACK_CLASS_H
