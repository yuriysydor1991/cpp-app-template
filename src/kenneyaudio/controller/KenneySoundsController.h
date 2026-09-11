#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/controller/IKenneySoundsController.h"
#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/player/KenneyRandomSound.h"
#include "src/kenneyaudio/sounds/IKenneySounds.h"

namespace kenneyaudio
{

/**
 * @brief The controller drawing a playable sound out of a set and playing it.
 *
 * Asks the player itself which file formats it decodes instead of naming any
 * of them, so a backend gained or swapped later changes nothing here and
 * nothing at all in the calling code.
 */
class KenneySoundsController : public IKenneySoundsController
{
 public:
  /**
   * @brief Constructs the controller over the given set and player.
   *
   * @param gsounds The sound set to draw of.
   * @param gplayer The player to sound the draws with, a nullptr one when the
   * project carries no audio backend.
   */
  KenneySoundsController(IKenneySoundsPtr gsounds,
                         IKenneySoundPlayerPtr gplayer);

  bool playable() const override;

  KenneySoundPtr draw() override;

  bool play(const KenneySoundPtr& sound) override;

  /**
   * @brief Creates the controller over the given set and the player the
   * project has been built with.
   *
   * @param gsounds The sound set to draw of.
   */
  static IKenneySoundsControllerPtr create(IKenneySoundsPtr gsounds);

  static IKenneySoundsControllerPtr create(IKenneySoundsPtr gsounds,
                                           IKenneySoundPlayerPtr gplayer);

 private:
  /**
   * @brief Gathers the sounds the player in use really decodes.
   */
  IKenneySounds::SoundsList playableSounds() const;

  IKenneySoundsPtr msounds;
  IKenneySoundPlayerPtr mplayer;
  KenneyRandomSound mdrawn;
};

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYSOUNDSCONTROLLER_CLASS_H
