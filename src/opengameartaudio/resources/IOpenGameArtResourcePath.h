#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTRESOURCEPATH_CLASS_H

#include <memory>
#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"

namespace opengameartaudio
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
class IOpenGameArtResourcePath
{
 public:
  using IOpenGameArtResourcePathPtr = std::shared_ptr<IOpenGameArtResourcePath>;

  virtual ~IOpenGameArtResourcePath() = default;

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
  virtual std::string of(const OpenGameArtSoundPtr& sound) const = 0;

  /**
   * @brief Gives the URI the toolkit resolves the given sound by, for the
   * calls taking an URI instead of a plain resource path.
   *
   * @param sound The sound of interest.
   *
   * @return Returns the resource URI, an empty string for a nullptr sound.
   */
  virtual std::string uriOf(const OpenGameArtSoundPtr& sound) const = 0;
};

using IOpenGameArtResourcePathPtr =
    IOpenGameArtResourcePath::IOpenGameArtResourcePathPtr;

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IOPENGAMEARTRESOURCEPATH_CLASS_H
