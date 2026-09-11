#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGRESOURCEPATH_CLASS_H

#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/resources/IOpenGameArtResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtResourcePath.h"

namespace opengameartaudio
{

/**
 * @brief The locator of a sound embedded through the GLib resource system.
 *
 * Resolves the sounds of a .gresource.xml manifest the
 * template_project_opengameart_audio_write_gresource function has written.
 */
class OpenGameArtGResourcePath : public OpenGameArtResourcePath
{
 public:
  explicit OpenGameArtGResourcePath(std::string gprefix);

  std::string of(const OpenGameArtSoundPtr& sound) const override;

  std::string uriOf(const OpenGameArtSoundPtr& sound) const override;

  static IOpenGameArtResourcePathPtr create();

  static IOpenGameArtResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The URI scheme the GLib calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "resource://";
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGRESOURCEPATH_CLASS_H
