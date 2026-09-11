#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/controller/KenneySoundsController.h"
#include "src/kenneyaudio/resources/KenneyGResourcePath.h"
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"
#include "src/kenneyaudio/sounds/KenneySounds.h"
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

  const auto sounds = kenneyaudio::KenneySounds::create();

  assert(sounds != nullptr);

  LOGI("The Kenney packs carry " << sounds->count() << " sounds at "
                                 << kenney_audio_decls::KENNEY_AUDIO_ROOT_DIR);

  const auto controller = kenneyaudio::KenneySoundsController::create(sounds);

  assert(controller != nullptr);

  const auto sound = controller->draw();

  if (sound == nullptr) {
    LOGW("No sound to play: fill the packs in and reconfigure the project");
    return 0;
  }

  LOGI("The drawn " << sound->alias() << " sound file: " << sound->filePath());
  LOGI("... embedded into the Qt resources: "
       << kenneyaudio::KenneyQtResourcePath::create()->of(sound));
  LOGI("... embedded into the GResource ones: "
       << kenneyaudio::KenneyGResourcePath::create()->of(sound));

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
