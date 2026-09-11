#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACK_CLASS_H

#include <memory>
#include <string>

/**
 * @brief The Kenney CC0 sound packs adaptor subsystem namespace.
 */
namespace kenneyaudio
{

/**
 * @brief A single Kenney sound pack.
 *
 * Kenney publishes it's sound effects as separate CC0 packs, each one
 * downloaded as an own archive and unpacked into an own subdirectory of the
 * packs root directory. Every descendant answers for one of those packs, so
 * the calling code names a pack by an instance instead of an enumeration value
 * and gains a new pack by a new descendant alone.
 */
class IKenneyPack
{
 public:
  using IKenneyPackPtr = std::shared_ptr<IKenneyPack>;

  virtual ~IKenneyPack() = default;

  /**
   * @brief Gives the pack name, which is also the name of it's subdirectory
   * inside the packs root directory.
   *
   * @return Returns the pack name, the "interface-sounds" one for example.
   */
  virtual std::string name() const = 0;
};

using IKenneyPackPtr = IKenneyPack::IKenneyPackPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYPACK_CLASS_H
