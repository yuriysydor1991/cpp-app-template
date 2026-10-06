#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/WhisperCPP/WhisperController.h"
#include "src/app/CMDParamNames.h"
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

  const std::string model = ctx->get_model_path().empty()
                                ? project_decls::PROJECT_WHISPER_MODEL_PATH
                                : ctx->get_model_path();

  auto whisper = whisperi::WhisperController::create();

  assert(whisper != nullptr);

  if (!whisper->init(model, project_decls::PROJECT_WHISPER_LANGUAGE)) {
    LOGE("Fail to init the speech recognition, point at a model with the "
         << CMDParamNames::MODELW << " or " << CMDParamNames::MODEL
         << " <path> command line parameter");
    return INVALID;
  }

  LOGI("Listening to the default microphone, press Ctrl+C to stop");

  // Insert your handling of the recognized speech here.
  while (!ctx->get_stop()) {
    const auto text = whisper->listen();

    if (!text.has_value()) {
      LOGE("Fail to listen to the default microphone");
      return INVALID;
    }

    if (!text->empty()) {
      LOGI(*text);
    }
  }

  return 0;
}

}  // namespace app
