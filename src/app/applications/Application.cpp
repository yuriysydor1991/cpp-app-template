#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/player/KenneyRandomSound.h"
#include "src/kenneyaudio/resources/KenneyGResourcePath.h"
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"
#include "src/kenneyaudio/sounds/KenneySounds.h"
#include "src/log/log.h"

#ifdef TEMPLATE_APP_SDL2_AUDIO
#include "src/kenneyaudio/player/KenneySdlSoundPlayer.h"
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

  const auto sounds = kenneyaudio::KenneySounds::create();

  assert(sounds != nullptr);

  LOGI("The Kenney packs carry " << sounds->count() << " sounds at "
                                 << kenney_audio_decls::KENNEY_AUDIO_ROOT_DIR);

  kenneyaudio::KenneyRandomSound drawn;

#ifdef TEMPLATE_APP_SDL2_AUDIO
  auto player = kenneyaudio::KenneySdlSoundPlayer::create();

  // The bare SDL2 decodes the RIFF/WAVE files alone, so the draw is narrowed
  // to what the player at hand really plays before it falls back to any sound
  // at all.
  auto sound = drawn.pick(sounds, DEMO_PLAYABLE_EXTENSION);

  if (sound == nullptr) {
    sound = drawn.pick(sounds);
  }
#else
  const kenneyaudio::IKenneySoundPlayerPtr player;

  auto sound = drawn.pick(sounds);
#endif

  if (sound == nullptr) {
    LOGW("No sound to play: fill the packs in and reconfigure the project");
    return 0;
  }

  LOGI("The drawn " << sound->alias() << " sound file: " << sound->filePath());
  LOGI("... embedded into the Qt resources: "
       << kenneyaudio::KenneyQtResourcePath::create()->of(sound));
  LOGI("... embedded into the GResource ones: "
       << kenneyaudio::KenneyGResourcePath::create()->of(sound));

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
