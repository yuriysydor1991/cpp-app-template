#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/player/FreesoundRandomSound.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"
#include "src/freesoundaudio/resources/FreesoundGResourcePath.h"
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"
#include "src/freesoundaudio/sounds/FreesoundSounds.h"
#include "src/log/log.h"

#ifdef TEMPLATE_APP_SDL2_AUDIO
#include "src/freesoundaudio/player/FreesoundSdlSoundPlayer.h"
#endif

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  const auto sounds = freesoundaudio::FreesoundSounds::create();

  assert(sounds != nullptr);

  LOGI("The Freesound categories carry "
       << sounds->count() << " sounds at "
       << freesound_audio_decls::FREESOUND_AUDIO_ROOT_DIR);

  freesoundaudio::FreesoundRandomSound drawn;

#ifdef TEMPLATE_APP_SDL2_AUDIO
  auto player = freesoundaudio::FreesoundSdlSoundPlayer::create();

  // The bare SDL2 decodes the RIFF/WAVE files alone, so the draw is narrowed
  // to what the player at hand really plays before it falls back to any sound
  // at all.
  auto sound = drawn.pick(sounds, DEMO_PLAYABLE_EXTENSION);

  if (sound == nullptr) {
    sound = drawn.pick(sounds);
  }
#else
  const freesoundaudio::IFreesoundSoundPlayerPtr player;

  auto sound = drawn.pick(sounds);
#endif

  if (sound == nullptr) {
    LOGW(
        "No sound to play: fill the categories in and reconfigure the project");
    return 0;
  }

  LOGI("The drawn " << sound->alias() << " sound file: " << sound->filePath());
  LOGI("... published under " << sound->license() << " at "
                              << sound->sourceUrl());
  LOGI("... embedded into the Qt resources: "
       << freesoundaudio::FreesoundQtResourcePath::create()->of(sound));
  LOGI("... embedded into the GResource ones: "
       << freesoundaudio::FreesoundGResourcePath::create()->of(sound));

  if (player == nullptr) {
    LOGI(
        "... and no player is built in: switch the ENABLE_SDL2_AUDIO option "
        "ON to hear it");
    return 0;
  }

  LOGI("Playing the " << sound->alias() << " sound ...");

  if (!player->play(sound)) {
    LOGW("The " << sound->alias() << " sound has not been played");
  }

  return 0;
}

}  // namespace app
