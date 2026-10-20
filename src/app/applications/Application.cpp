#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/TTS/AudioPlayer.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/WavWriter.h"
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

  const std::string& text = ctx->get_text().empty()
                                ? project_decls::PROJECT_TTS_TEXT
                                : ctx->get_text();
  const std::string voice =
      ctx->get_voice().empty()
          ? DataLocator::locate(project_decls::PROJECT_TTS_VOICE)
          : ctx->get_voice();

  auto synthesizer = tts::ISpeechSynthesizer::create();

  assert(synthesizer != nullptr);

  // Insert your own text to speak here.
  const auto speech = synthesizer->synthesize(text, voice);

  if (!speech.has_value()) {
    LOGE("Fail to synthesize the speech, pick another voice with the "
         << CMDParamNames::VOICEW << " or " << CMDParamNames::VOICE
         << " <voice> command line parameter");
    return INVALID;
  }

  if (!ctx->get_output_path().empty()) {
    return tts::WavWriter::create()->write(*speech, ctx->get_output_path())
               ? 0
               : INVALID;
  }

  // The Ctrl+C keys stop the playback before the speech end.
  const auto stopped = [&ctx] { return ctx->get_stop(); };

  return tts::AudioPlayer::create()->play(*speech, stopped) ? 0 : INVALID;
}

}  // namespace app
