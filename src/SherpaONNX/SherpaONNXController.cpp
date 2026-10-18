#include "src/SherpaONNX/SherpaONNXController.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#include "src/SherpaONNX/SherpaONNXModel.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"
#include "src/log/log.h"

namespace sherpaonnx
{

namespace
{

/**
 * @brief Splits the voice into the model directory and the speaker id of the
 * :<id> suffix, the first speaker one for no such suffix.
 */
std::pair<std::string, std::int32_t> split(const std::string& voice)
{
  const auto colon = voice.rfind(':');
  const char* const end = voice.data() + voice.size();
  std::uint16_t speaker{0U};

  if (colon == std::string::npos) {
    return {voice, 0};
  }

  const auto [last, error] =
      std::from_chars(voice.data() + colon + 1U, end, speaker);

  // A colon of no number after it is the part of the directory.
  if (error != std::errc{} || last != end) {
    return {voice, 0};
  }

  return {voice.substr(0U, colon), speaker};
}

/// @brief Converts the [-1, 1] samples of the sherpa-onnx into the 16-bit ones.
tts::Speech::samples pcm_of(const std::vector<float>& samples)
{
  constexpr float MAX_SAMPLE{std::numeric_limits<tts::Speech::sample>::max()};

  tts::Speech::samples pcm(samples.size());

  std::transform(
      samples.cbegin(), samples.cend(), pcm.begin(), [](const float sample) {
        return static_cast<tts::Speech::sample>(
            std::lround(std::clamp(sample, -1.0F, 1.0F) * MAX_SAMPLE));
      });

  return pcm;
}

}  // namespace

const sherpa_onnx::cxx::OfflineTts* SherpaONNXController::load(
    const std::string& directory)
{
  if (mtts.has_value() && mdirectory == directory) {
    return &*mtts;
  }

  mtts.reset();

  const auto model = SherpaONNXModel::detect(directory);

  if (model == nullptr) {
    LOGE("No Kokoro or VITS model of the sherpa-onnx in the "
         << directory
         << " directory, unpack one of the sherpa-onnx tts-models release "
            "archives there");
    return nullptr;
  }

  auto tts = sherpa_onnx::cxx::OfflineTts::Create(model->configure());

  if (tts.Get() == nullptr) {
    LOGE("Fail to load the sherpa-onnx model of the " << directory
                                                      << " directory");
    return nullptr;
  }

  const auto& loaded = mtts.emplace(std::move(tts));

  mdirectory = directory;

  LOGD("The sherpa-onnx model of the " << directory << " directory is loaded");

  return &loaded;
}

SherpaONNXController::result SherpaONNXController::synthesize(
    const std::string& text, const std::string& voice)
{
  const auto [directory, speaker] = split(voice);
  const auto* const engine = load(directory);

  if (engine == nullptr) {
    return {};
  }

  if (speaker > 0 && speaker >= engine->NumSpeakers()) {
    LOGE("The sherpa-onnx model of the " << directory << " directory has no "
                                         << speaker << " speaker");
    return {};
  }

  const auto audio = engine->Generate(text, speaker);

  LOGD("Synthesized " << audio.samples.size() << " samples with the " << voice
                      << " sherpa-onnx voice");

  return tts::Speech{pcm_of(audio.samples), audio.sample_rate};
}

}  // namespace sherpaonnx

namespace tts
{

ISpeechSynthesizerPtr ISpeechSynthesizer::create()
{
  return std::make_shared<sherpaonnx::SherpaONNXController>();
}

}  // namespace tts
