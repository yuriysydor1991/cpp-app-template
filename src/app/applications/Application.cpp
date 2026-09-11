#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "opengameart-audio-decls.h"
#include "src/log/log.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"
#include "src/opengameartaudio/resources/OpenGameArtGResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

#ifdef TEMPLATE_APP_SDL2_AUDIO
#include "src/opengameartaudio/player/OpenGameArtSdlSoundPlayer.h"
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

  const auto sounds = opengameartaudio::OpenGameArtSounds::create();

  assert(sounds != nullptr);

  LOGI("The OpenGameArt packs carry "
       << sounds->count() << " sounds at "
       << opengameart_audio_decls::OPENGAMEART_AUDIO_ROOT_DIR);

  opengameartaudio::OpenGameArtRandomSound drawn;

#ifdef TEMPLATE_APP_SDL2_AUDIO
  auto player = opengameartaudio::OpenGameArtSdlSoundPlayer::create();

  // The bare SDL2 decodes the RIFF/WAVE files alone, so the draw is narrowed
  // to what the player at hand really plays before it falls back to any sound
  // at all.
  auto sound = drawn.pick(sounds, DEMO_PLAYABLE_EXTENSION);

  if (sound == nullptr) {
    sound = drawn.pick(sounds);
  }
#else
  const opengameartaudio::IOpenGameArtSoundPlayerPtr player;

  auto sound = drawn.pick(sounds);
#endif

  if (sound == nullptr) {
    LOGW("No sound to play: fill the packs in and reconfigure the project");
    return 0;
  }

  LOGI("The drawn " << sound->alias() << " sound file: " << sound->filePath());
  LOGI("... published under: " << sound->pack()->license());
  LOGI("... embedded into the Qt resources: "
       << opengameartaudio::OpenGameArtQtResourcePath::create()->of(sound));
  LOGI("... embedded into the GResource ones: "
       << opengameartaudio::OpenGameArtGResourcePath::create()->of(sound));

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
