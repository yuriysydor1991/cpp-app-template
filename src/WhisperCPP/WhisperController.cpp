#include "src/WhisperCPP/WhisperController.h"

#include <ggml-backend.h>
#include <whisper.h>

#include <memory>
#include <string>
#include <thread>

#include "src/WhisperCPP/Microphone.h"
#include "src/WhisperCPP/UtteranceDetector.h"
#include "src/log/log.h"

namespace whisperi
{

namespace
{

/**
 * @brief Routes the whisper.cpp and the ggml messages into the project
 * logger. A model load alone writes dozens of the info ones, so they go at the
 * debug level and the rest of the non failure ones at the trace level.
 */
void log_message(const ggml_log_level level, const char* const text,
                 [[maybe_unused]] void* const userData)
{
  std::string message{text != nullptr ? text : ""};

  if (!message.empty() && message.back() == '\n') {
    message.pop_back();
  }

  if (message.empty()) {
    return;
  }

  switch (level) {
    case GGML_LOG_LEVEL_ERROR:
      LOGE(message);
      break;
    case GGML_LOG_LEVEL_WARN:
      LOGW(message);
      break;
    case GGML_LOG_LEVEL_INFO:
      LOGD(message);
      break;
    default:
      LOGT(message);
  }
}

/**
 * @brief Hands the whisper.cpp and the ggml messages over to the project
 * logger and loads the ggml backends, both once per process. A ggml built
 * with the dynamically loaded backends (the Debian packages one, for example)
 * computes nothing without them, while a statically linked one finds nothing
 * to load.
 */
void prepare_whisper()
{
  [[maybe_unused]] static const bool prepared = [] {
    whisper_log_set(log_message, nullptr);
    ggml_backend_load_all();
    return true;
  }();
}

}  // namespace

WhisperController::~WhisperController() { whisper_free(context); }

WhisperController::WhisperController()
    : microphone{Microphone::create()}, detector{WHISPER_SAMPLE_RATE}
{
}

bool WhisperController::init(const std::string& modelPath,
                             const std::string& language)
{
  prepare_whisper();

  // The whisper.cpp takes the language for an index into it's tables, so an
  // unknown one is refused right here.
  if (language != "auto" && whisper_lang_id(language.c_str()) < 0) {
    LOGE("Unknown spoken language: " << language);
    return false;
  }

  whisper_free(context);

  context = whisper_init_from_file_with_params(
      modelPath.c_str(), whisper_context_default_params());

  if (context == nullptr) {
    LOGE("Fail to load the " << modelPath << " whisper model");
    return false;
  }

  spokenLanguage = language;

  LOGD("The " << modelPath << " whisper model is loaded");

  return true;
}

WhisperController::result WhisperController::listen()
{
  if (context == nullptr) {
    LOGE("The whisper controller is not initialized");
    return {};
  }

  if (!microphone->open(WHISPER_SAMPLE_RATE)) {
    return {};
  }

  std::this_thread::sleep_for(LISTEN_STEP);

  const auto utterance = detector.feed(microphone->read());

  if (utterance.empty()) {
    return result{""};
  }

  LOGD("Transcribing the " << utterance.size() * 1000U / WHISPER_SAMPLE_RATE
                           << " ms utterance");

  return transcribe(utterance);
}

WhisperController::result WhisperController::transcribe(const samples& audio)
{
  if (context == nullptr) {
    LOGE("The whisper controller is not initialized");
    return {};
  }

  auto params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);

  params.print_progress = false;
  params.print_timestamps = false;
  // Every utterance stands on it's own, while the previous text given as the
  // prompt makes the whisper repeat it now and then.
  params.no_context = true;
  // The non speech tokens are the (music) and the [BLANK_AUDIO] like ones.
  params.suppress_nst = true;
  params.language =
      whisper_is_multilingual(context) != 0 ? spokenLanguage.c_str() : "en";

  if (whisper_full(context, params, audio.data(),
                   static_cast<int>(audio.size())) != 0) {
    LOGE("Fail to transcribe the " << audio.size() << " samples");
    return {};
  }

  std::string text;

  for (int segment = 0; segment < whisper_full_n_segments(context); ++segment) {
    text += whisper_full_get_segment_text(context, segment);
  }

  // Every segment starts with a space.
  const auto first = text.find_first_not_of(' ');

  return first == std::string::npos
             ? std::string{}
             : text.substr(first, text.find_last_not_of(' ') - first + 1U);
}

WhisperControllerPtr WhisperController::create()
{
  return std::make_shared<WhisperController>();
}

}  // namespace whisperi
