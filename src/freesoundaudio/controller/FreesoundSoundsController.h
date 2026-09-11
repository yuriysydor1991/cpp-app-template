#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/controller/IFreesoundSoundsController.h"
#include "src/freesoundaudio/player/FreesoundRandomSound.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"

namespace freesoundaudio
{

/**
 * @brief The controller drawing a playable sound out of a set and playing it.
 *
 * Asks the player itself which file formats it decodes instead of naming any
 * of them, so a backend gained or swapped later changes nothing here and
 * nothing at all in the calling code.
 */
class FreesoundSoundsController : public IFreesoundSoundsController
{
 public:
  /**
   * @brief Constructs the controller over the given set and player.
   *
   * @param gsounds The sound set to draw of.
   * @param gplayer The player to sound the draws with, a nullptr one when the
   * project carries no audio backend.
   */
  FreesoundSoundsController(IFreesoundSoundsPtr gsounds,
                            IFreesoundSoundPlayerPtr gplayer);

  bool playable() const override;

  FreesoundSoundPtr draw() override;

  bool play(const FreesoundSoundPtr& sound) override;

  /**
   * @brief Creates the controller over the given set and the player the
   * project has been built with.
   *
   * @param gsounds The sound set to draw of.
   */
  static IFreesoundSoundsControllerPtr create(IFreesoundSoundsPtr gsounds);

  static IFreesoundSoundsControllerPtr create(IFreesoundSoundsPtr gsounds,
                                              IFreesoundSoundPlayerPtr gplayer);

 private:
  /**
   * @brief Gathers the sounds the player in use really decodes.
   */
  IFreesoundSounds::SoundsList playableSounds() const;

  IFreesoundSoundsPtr msounds;
  IFreesoundSoundPlayerPtr mplayer;
  FreesoundRandomSound mdrawn;
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
