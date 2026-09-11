#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTRESOURCEPATH_CLASS_H

#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/resources/IOpenGameArtResourcePath.h"

namespace opengameartaudio
{

/**
 * @brief The prefix handling every resource system locator shares.
 *
 * Keeps the given prefix in the single leading slash and no trailing slash
 * form, so the descendants concatenate it with a sound alias and nothing else.
 */
class OpenGameArtResourcePath : public IOpenGameArtResourcePath
{
 public:
  /**
   * @brief Constructs the locator placing the sounds under the given prefix.
   *
   * @param gprefix The resource system prefix of the manifest in use.
   */
  explicit OpenGameArtResourcePath(std::string gprefix);

  const std::string& prefix() const override;

 protected:
  /**
   * @brief Gives the prefixed alias of the given sound, which every resource
   * system path of that sound is built upon.
   *
   * @param sound The sound of interest.
   *
   * @return Returns the "<prefix>/<pack>/<path>" path, an empty string for a
   * nullptr sound.
   */
  std::string prefixedAlias(const OpenGameArtSoundPtr& sound) const;

 private:
  /**
   * @brief Brings the given prefix to the single leading slash and no trailing
   * slash form.
   *
   * @param gprefix The prefix to normalize.
   *
   * @return Returns the normalized prefix.
   */
  static std::string normalized(std::string gprefix);

  std::string mprefix;
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTRESOURCEPATH_CLASS_H
