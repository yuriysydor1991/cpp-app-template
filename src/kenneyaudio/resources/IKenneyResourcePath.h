#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYRESOURCEPATH_CLASS_H

#include <memory>
#include <string>

#include "src/kenneyaudio/KenneySound.h"

namespace kenneyaudio
{

/**
 * @brief The run time locator of a sound embedded into the resource system of
 * a GUI toolkit.
 *
 * A sound compiled into a binary is no file any more, so every toolkit
 * resolves it by a path of it's own resource system. Every descendant answers
 * for one of those systems and keys the sound by the very alias the generated
 * resource manifest of that system carries.
 */
class IKenneyResourcePath
{
 public:
  using IKenneyResourcePathPtr = std::shared_ptr<IKenneyResourcePath>;

  virtual ~IKenneyResourcePath() = default;

  /**
   * @brief Gives the resource system prefix every sound path sits under.
   */
  virtual const std::string& prefix() const = 0;

  /**
   * @brief Gives the path the toolkit resolves the given sound by.
   *
   * @param sound The sound of interest.
   *
   * @return Returns the resource path, an empty string for a nullptr sound.
   */
  virtual std::string of(const KenneySoundPtr& sound) const = 0;

  /**
   * @brief Gives the URI the toolkit resolves the given sound by, for the
   * calls taking an URI instead of a plain resource path.
   *
   * @param sound The sound of interest.
   *
   * @return Returns the resource URI, an empty string for a nullptr sound.
   */
  virtual std::string uriOf(const KenneySoundPtr& sound) const = 0;
};

using IKenneyResourcePathPtr = IKenneyResourcePath::IKenneyResourcePathPtr;

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IKENNEYRESOURCEPATH_CLASS_H
