#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYQTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYQTRESOURCEPATH_CLASS_H

#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/resources/IKenneyResourcePath.h"
#include "src/kenneyaudio/resources/KenneyResourcePath.h"

namespace kenneyaudio
{

/**
 * @brief The locator of a sound embedded through the Qt resource system.
 *
 * Resolves the sounds of a .qrc manifest the
 * template_project_kenney_audio_write_qrc function has written.
 */
class KenneyQtResourcePath : public KenneyResourcePath
{
 public:
  explicit KenneyQtResourcePath(std::string gprefix);

  std::string of(const KenneySoundPtr& sound) const override;

  std::string uriOf(const KenneySoundPtr& sound) const override;

  static IKenneyResourcePathPtr create();

  static IKenneyResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The leading mark every compiled in Qt resource path carries.
  inline static const std::string RESOURCE_MARK = ":";

  /// @brief The URI scheme the Qt calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "qrc:";
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYQTRESOURCEPATH_CLASS_H
