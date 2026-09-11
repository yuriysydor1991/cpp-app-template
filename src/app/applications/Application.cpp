#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/controller/FreesoundSoundsController.h"
#include "src/freesoundaudio/resources/FreesoundGResourcePath.h"
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"
#include "src/freesoundaudio/sounds/FreesoundSounds.h"
#include "src/log/log.h"

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

  LOGI("The Freesound packs carry "
       << sounds->count() << " sounds at "
       << freesound_audio_decls::FREESOUND_AUDIO_ROOT_DIR);

  const auto controller =
      freesoundaudio::FreesoundSoundsController::create(sounds);

  assert(controller != nullptr);

  const auto sound = controller->draw();

  if (sound == nullptr) {
    LOGW("No sound to play: fill the packs in and reconfigure the project");
    return 0;
  }

  LOGI("The drawn " << sound->alias() << " sound file: " << sound->filePath());
  LOGI("... published under " << sound->license() << " at "
                              << sound->sourceUrl());
  LOGI("... embedded into the Qt resources: "
       << freesoundaudio::FreesoundQtResourcePath::create()->of(sound));
  LOGI("... embedded into the GResource ones: "
       << freesoundaudio::FreesoundGResourcePath::create()->of(sound));

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
