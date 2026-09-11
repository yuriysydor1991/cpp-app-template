#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTQTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTQTRESOURCEPATH_CLASS_H

#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/resources/IOpenGameArtResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtResourcePath.h"

namespace opengameartaudio
{

/**
 * @brief The locator of a sound embedded through the Qt resource system.
 *
 * Resolves the sounds of a .qrc manifest the
 * template_project_opengameart_audio_write_qrc function has written.
 */
class OpenGameArtQtResourcePath : public OpenGameArtResourcePath
{
 public:
  explicit OpenGameArtQtResourcePath(std::string gprefix);

  std::string of(const OpenGameArtSoundPtr& sound) const override;

  std::string uriOf(const OpenGameArtSoundPtr& sound) const override;

  static IOpenGameArtResourcePathPtr create();

  static IOpenGameArtResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The leading mark every compiled in Qt resource path carries.
  inline static const std::string RESOURCE_MARK = ":";

  /// @brief The URI scheme the Qt calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "qrc:";
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTQTRESOURCEPATH_CLASS_H
