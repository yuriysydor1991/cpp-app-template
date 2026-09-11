#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "opengameart-audio-decls.h"
#include "src/log/log.h"
#include "src/opengameartaudio/controller/OpenGameArtSoundsController.h"
#include "src/opengameartaudio/resources/OpenGameArtGResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

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

  const auto controller =
      opengameartaudio::OpenGameArtSoundsController::create(sounds);

  assert(controller != nullptr);

  const auto sound = controller->draw();

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

  if (!controller->playable()) {
    LOGI("... and no audio backend is built in, so nothing sounds it here");
    return 0;
  }

  LOGI("Playing the " << sound->alias() << " sound ...");

  if (!controller->play(sound)) {
    LOGW("The " << sound->alias() << " sound has not been played");
  }

  return 0;
}

}  // namespace app
