#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/STT/SpeechListener.h"
#include "src/app/CMDParamNames.h"
#include "src/app/DataLocator.h"
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

  const std::string model =
      ctx->get_model_path().empty()
          ? DataLocator::locate(project_decls::PROJECT_STT_MODEL)
          : ctx->get_model_path();

  auto listener = stt::SpeechListener::create();

  assert(listener != nullptr);

  if (!listener->init(model)) {
    LOGE("Fail to init the speech recognition, point at a model with the "
         << CMDParamNames::MODELW << " or " << CMDParamNames::MODEL
         << " <path> command line parameter");
    return INVALID;
  }

  LOGI("Listening to the default microphone, press Ctrl+C to stop");

  // Insert your handling of the recognized speech here.
  while (!ctx->get_stop()) {
    const auto text = listener->listen();

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
