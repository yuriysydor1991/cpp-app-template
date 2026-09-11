#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACK_CLASS_H

#include <string>

#include "src/kenneyaudio/packs/IKenneyPack.h"

namespace kenneyaudio
{

/**
 * @brief A Kenney sound pack named at the run time.
 *
 * The packs to make available are a build option rather than a fixed set, so
 * one descendant carrying the configured name serves every pack instead of a
 * hand written class per pack.
 */
class KenneyPack : public IKenneyPack
{
 public:
  /**
   * @brief Constructs the pack of the given name.
   *
   * @param gname The pack name, the "interface-sounds" one for example.
   */
  explicit KenneyPack(std::string gname);

  std::string name() const override;

  static IKenneyPackPtr create(std::string gname);

 private:
  std::string mname;
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYPACK_CLASS_H
