#include "src/RHVoice/RHVoiceController.h"

#include <RHVoice.h>

#include <memory>
#include <string>
#include <utility>

#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"
#include "src/log/log.h"

namespace rhvoice
{

namespace
{

/// @brief The sample rate and the samples of the speech the RHVoice
/// callbacks collect, which the message hands over as the user data.
using Collected = std::pair<int, tts::Speech::samples>;

/// @brief Keeps the sample rate of the voice speaking the message.
///
/// @return Returns nonzero to go on with the synthesis.
int set_sample_rate(const int sampleRate, void* const userData)
{
  static_cast<Collected*>(userData)->first = sampleRate;

  return 1;
}

/// @brief Collects the synthesized samples of the message.
///
/// @return Returns nonzero to go on with the synthesis.
int play_speech(const short* const samples, const unsigned int count,
                void* const userData)
{
  auto& pcm = static_cast<Collected*>(userData)->second;

  pcm.insert(pcm.end(), samples, samples + count);

  return 1;
}

}  // namespace

RHVoiceController::~RHVoiceController()
{
  if (engine != nullptr) {
    RHVoice_delete_tts_engine(engine);
  }
}

bool RHVoiceController::init()
{
  if (engine != nullptr) {
    return true;
  }

  // No paths make it take the RHVOICE_DATA_PATH and the RHVOICE_CONFIG_PATH
  // environment variable ones, then the ones of the installed library.
  RHVoice_init_params params{};

  params.callbacks.set_sample_rate = set_sample_rate;
  params.callbacks.play_speech = play_speech;

  engine = RHVoice_new_tts_engine(&params);

  if (engine == nullptr) {
    LOGE(
        "Fail to init the RHVoice, check it's voices are installed or point "
        "at them with the RHVOICE_DATA_PATH environment variable");
    return false;
  }

  LOGD("The RHVoice engine is created");

  return true;
}

RHVoiceController::result RHVoiceController::synthesize(
    const std::string& text, const std::string& voice)
{
  if (!init()) {
    return {};
  }

  // The zero absolute and the unit relative rate, pitch and volume keep the
  // ones of the voice.
  RHVoice_synth_params params{};

  params.voice_profile = voice.c_str();
  params.relative_rate = params.relative_pitch = params.relative_volume = 1.0;

  Collected speech;

  RHVoice_message message = RHVoice_new_message(
      engine, text.c_str(), static_cast<unsigned int>(text.size()),
      RHVoice_message_text, &params, &speech);

  if (message == nullptr) {
    LOGE("Fail to speak with the "
         << voice << " RHVoice voice, it is unknown or the text is empty");
    return {};
  }

  const bool spoken = RHVoice_speak(message) != 0;

  RHVoice_delete_message(message);

  if (!spoken) {
    LOGE("Fail to synthesize the speech with the " << voice
                                                   << " RHVoice voice");
    return {};
  }

  LOGD("Synthesized " << speech.second.size() << " samples with the " << voice
                      << " RHVoice voice");

  return tts::Speech{std::move(speech.second), speech.first};
}

}  // namespace rhvoice

namespace tts
{

ISpeechSynthesizerPtr ISpeechSynthesizer::create()
{
  return std::make_shared<rhvoice::RHVoiceController>();
}

}  // namespace tts
