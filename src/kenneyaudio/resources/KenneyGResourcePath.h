#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGRESOURCEPATH_CLASS_H

#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/resources/IKenneyResourcePath.h"
#include "src/kenneyaudio/resources/KenneyResourcePath.h"

namespace kenneyaudio
{

/**
 * @brief The locator of a sound embedded through the GLib resource system.
 *
 * Resolves the sounds of a .gresource.xml manifest the
 * template_project_kenney_audio_write_gresource function has written.
 */
class KenneyGResourcePath : public KenneyResourcePath
{
 public:
  explicit KenneyGResourcePath(std::string gprefix);

  std::string of(const KenneySoundPtr& sound) const override;

  std::string uriOf(const KenneySoundPtr& sound) const override;

  static IKenneyResourcePathPtr create();

  static IKenneyResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The URI scheme the GLib calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "resource://";
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGRESOURCEPATH_CLASS_H
