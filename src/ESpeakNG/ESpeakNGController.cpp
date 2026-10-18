#include "src/ESpeakNG/ESpeakNGController.h"

#include <espeak-ng/espeak_ng.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"
#include "src/log/log.h"

namespace espeakng
{

namespace
{

/// @brief The room for the longest status description of the eSpeak NG.
constexpr std::size_t MESSAGE_SIZE{512U};

/// @brief Gives the eSpeak NG description of the given status code.
std::string describe(const espeak_ng_STATUS status)
{
  std::array<char, MESSAGE_SIZE> message{};

  espeak_ng_GetStatusCodeMessage(status, message.data(), message.size());

  return message.data();
}

/**
 * @brief Collects the synthesized samples into the tts::Speech::samples the
 * synthesis call hands over as the user data. The null samples mark the end of
 * the synthesis.
 *
 * @return Returns zero to go on with the synthesis.
 */
int collect(short* const wav, const int count, espeak_EVENT* const events)
{
  if (wav != nullptr && count > 0 && events != nullptr &&
      events->user_data != nullptr) {
    auto& pcm = *static_cast<tts::Speech::samples*>(events->user_data);

    pcm.insert(pcm.end(), wav, wav + count);
  }

  return 0;
}

}  // namespace

ESpeakNGController::~ESpeakNGController()
{
  if (initialized) {
    espeak_ng_Terminate();
  }
}

bool ESpeakNGController::init()
{
  if (initialized) {
    return true;
  }

  // No path makes it take the ESPEAK_DATA_PATH environment variable one, then
  // the one of the installed library.
  espeak_ng_InitializePath(nullptr);

  espeak_ng_ERROR_CONTEXT context{nullptr};
  espeak_ng_STATUS status = espeak_ng_Initialize(&context);

  espeak_ng_ClearErrorContext(&context);

  if (status != ENS_OK) {
    LOGE(
        "Fail to init the eSpeak NG, check it's data or point at it with the "
        "ESPEAK_DATA_PATH environment variable: "
        << describe(status));
    return false;
  }

  status = espeak_ng_InitializeOutput(ENOUTPUT_MODE_SYNCHRONOUS, 0, nullptr);

  if (status != ENS_OK) {
    LOGE("Fail to init the eSpeak NG output: " << describe(status));
    espeak_ng_Terminate();
    return false;
  }

  espeak_SetSynthCallback(collect);

  initialized = true;

  LOGD("The eSpeak NG is initialized");

  return true;
}

ESpeakNGController::result ESpeakNGController::synthesize(
    const std::string& text, const std::string& voice)
{
  if (!init()) {
    return {};
  }

  espeak_ng_STATUS status = espeak_ng_SetVoiceByName(voice.c_str());

  if (status != ENS_OK) {
    LOGE("Fail to select the " << voice
                               << " eSpeak NG voice: " << describe(status));
    return {};
  }

  tts::Speech::samples pcm;

  // The synchronous mode collects the whole speech before the call returns.
  // The size covers the terminating null character.
  status =
      espeak_ng_Synthesize(text.c_str(), text.size() + 1U, 0U, POS_CHARACTER,
                           0U, espeakCHARS_UTF8, nullptr, &pcm);

  if (status != ENS_OK) {
    LOGE("Fail to synthesize the speech: " << describe(status));
    return {};
  }

  LOGD("Synthesized " << pcm.size() << " samples with the " << voice
                      << " eSpeak NG voice");

  return tts::Speech{std::move(pcm), espeak_ng_GetSampleRate()};
}

}  // namespace espeakng

namespace tts
{

ISpeechSynthesizerPtr ISpeechSynthesizer::create()
{
  return std::make_shared<espeakng::ESpeakNGController>();
}

}  // namespace tts
