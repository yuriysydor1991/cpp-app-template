#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/controller/IOpenGameArtSoundsController.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"
#include "src/opengameartaudio/sounds/IOpenGameArtSounds.h"

namespace opengameartaudio
{

/**
 * @brief The controller drawing a playable sound out of a set and playing it.
 *
 * Asks the player itself which file formats it decodes instead of naming any
 * of them, so a backend gained or swapped later changes nothing here and
 * nothing at all in the calling code.
 */
class OpenGameArtSoundsController : public IOpenGameArtSoundsController
{
 public:
  /**
   * @brief Constructs the controller over the given set and player.
   *
   * @param gsounds The sound set to draw of.
   * @param gplayer The player to sound the draws with, a nullptr one when the
   * project carries no audio backend.
   */
  OpenGameArtSoundsController(IOpenGameArtSoundsPtr gsounds,
                              IOpenGameArtSoundPlayerPtr gplayer);

  bool playable() const override;

  OpenGameArtSoundPtr draw() override;

  bool play(const OpenGameArtSoundPtr& sound) override;

  /**
   * @brief Creates the controller over the given set and the player the
   * project has been built with.
   *
   * @param gsounds The sound set to draw of.
   */
  static IOpenGameArtSoundsControllerPtr create(IOpenGameArtSoundsPtr gsounds);

  static IOpenGameArtSoundsControllerPtr create(
      IOpenGameArtSoundsPtr gsounds, IOpenGameArtSoundPlayerPtr gplayer);

 private:
  /**
   * @brief Gathers the sounds the player in use really decodes.
   */
  IOpenGameArtSounds::SoundsList playableSounds() const;

  IOpenGameArtSoundsPtr msounds;
  IOpenGameArtSoundPlayerPtr mplayer;
  OpenGameArtRandomSound mdrawn;
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
