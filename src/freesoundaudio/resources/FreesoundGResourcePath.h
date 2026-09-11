#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGRESOURCEPATH_CLASS_H

#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/resources/FreesoundResourcePath.h"
#include "src/freesoundaudio/resources/IFreesoundResourcePath.h"

namespace freesoundaudio
{

/**
 * @brief The locator of a sound embedded through the GLib resource system.
 *
 * Resolves the sounds of a .gresource.xml manifest the
 * template_project_freesound_audio_write_gresource function has written.
 */
class FreesoundGResourcePath : public FreesoundResourcePath
{
 public:
  explicit FreesoundGResourcePath(std::string gprefix);

  std::string of(const FreesoundSoundPtr& sound) const override;

  std::string uriOf(const FreesoundSoundPtr& sound) const override;

  static IFreesoundResourcePathPtr create();

  static IFreesoundResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The URI scheme the GLib calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "resource://";
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGRESOURCEPATH_CLASS_H
