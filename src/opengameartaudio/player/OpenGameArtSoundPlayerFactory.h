#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDPLAYERFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDPLAYERFACTORY_CLASS_H

#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"

namespace opengameartaudio
{

/**
 * @brief The source of the player the project has been built with.
 *
 * Which audio backend - if any at all - ends up inside the binary is a build
 * option, so the answer comes from the implementation file the CMake build
 * picks instead of a preprocessor branch in every calling place.
 */
class OpenGameArtSoundPlayerFactory
{
 public:
  /**
   * @brief Gives the player of the backend built in.
   *
   * @return Returns the player, a nullptr one when the project carries no
   * audio backend at all.
   */
  static IOpenGameArtSoundPlayerPtr create();
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDPLAYERFACTORY_CLASS_H
