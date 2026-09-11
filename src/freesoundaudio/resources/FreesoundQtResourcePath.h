#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDQTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDQTRESOURCEPATH_CLASS_H

#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/resources/FreesoundResourcePath.h"
#include "src/freesoundaudio/resources/IFreesoundResourcePath.h"

namespace freesoundaudio
{

/**
 * @brief The locator of a sound embedded through the Qt resource system.
 *
 * Resolves the sounds of a .qrc manifest the
 * template_project_freesound_audio_write_qrc function has written.
 */
class FreesoundQtResourcePath : public FreesoundResourcePath
{
 public:
  explicit FreesoundQtResourcePath(std::string gprefix);

  std::string of(const FreesoundSoundPtr& sound) const override;

  std::string uriOf(const FreesoundSoundPtr& sound) const override;

  static IFreesoundResourcePathPtr create();

  static IFreesoundResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The leading mark every compiled in Qt resource path carries.
  inline static const std::string RESOURCE_MARK = ":";

  /// @brief The URI scheme the Qt calls taking an URI expect.
  inline static const std::string RESOURCE_SCHEME = "qrc:";
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDQTRESOURCEPATH_CLASS_H
