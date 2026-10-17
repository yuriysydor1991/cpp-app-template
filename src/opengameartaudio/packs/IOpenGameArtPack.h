#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACK_CLASS_H

#include <memory>
#include <string>

/**
 * @brief The OpenGameArt CC0 sound packs adaptor subsystem namespace.
 */
namespace opengameartaudio
{

/**
 * @brief A single OpenGameArt sound pack.
 *
 * OpenGameArt publishes it's sound effects as separate CC0 packs, each one
 * downloaded as an own archive and unpacked into an own subdirectory of the
 * packs root directory. Every descendant answers for one of those packs, so
 * the calling code names a pack by an instance instead of an enumeration value
 * and gains a new pack by a new descendant alone.
 */
class IOpenGameArtPack
{
 public:
  using IOpenGameArtPackPtr = std::shared_ptr<IOpenGameArtPack>;

  virtual ~IOpenGameArtPack() = default;

  /**
   * @brief Gives the pack name, which is also the name of it's subdirectory
   * inside the packs root directory.
   *
   * @return Returns the pack name, the "interface-sounds" one for example.
   */
  virtual std::string name() const = 0;

  /**
   * @brief Gives the license the pack was published under.
   *
   * OpenGameArt hosts it's submissions under several different licenses, so
   * the one recorded in the packs manifest travels with the pack itself
   * instead of being assumed by the calling code.
   *
   * @return Returns the license, the "CC0-1.0" one for example.
   */
  virtual std::string license() const = 0;
};

using IOpenGameArtPackPtr = IOpenGameArtPack::IOpenGameArtPackPtr;

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTPACK_CLASS_H
