#include "src/PiperTTS/PiperController.h"

#include <dlfcn.h>
#include <piper.h>

#include <algorithm>
#include <exception>
#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <utility>

#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"
#include "src/log/log.h"

namespace pipertts
{

namespace
{

/// @brief The loudest 16-bit sample, the one of the loudest Piper sample.
constexpr float LOUDEST{32767.0F};

/// @brief Converts the Piper sample of the -1 to 1 range into the 16-bit one.
tts::Speech::sample to_pcm(const float sample)
{
  return static_cast<tts::Speech::sample>(
      std::clamp(sample * LOUDEST, -LOUDEST, LOUDEST));
}

/**
 * @brief Gives the espeak-ng-data directory the enabler installs beside the
 * libpiper, so the build directory and the relocated installations find it.
 */
std::string espeak_data_path()
{
  Dl_info library{};

  if (dladdr(reinterpret_cast<const void*>(&piper_create), &library) == 0 ||
      library.dli_fname == nullptr) {
    return {};
  }

  return (std::filesystem::path{library.dli_fname}.parent_path() /
          "espeak-ng-data")
      .string();
}

}  // namespace

bool PiperController::load(const std::string& voice)
{
  if (msynthesizer != nullptr && mvoice == voice) {
    return true;
  }

  if (!std::filesystem::is_regular_file(voice) ||
      !std::filesystem::is_regular_file(voice + ".json")) {
    LOGE("No " << voice
               << " Piper voice model with it's .json config beside it");
    return false;
  }

  // The loaded voice goes first, since freeing it terminates the espeak-ng the
  // next one initializes.
  msynthesizer.reset();
  msynthesizer.reset(
      piper_create(voice.c_str(), nullptr, espeak_data_path().c_str()));

  if (msynthesizer == nullptr) {
    LOGE("Fail to load the " << voice << " Piper voice");
    return false;
  }

  mvoice = voice;

  LOGD("The " << voice << " Piper voice is loaded");

  return true;
}

PiperController::result PiperController::synthesize(const std::string& text,
                                                    const std::string& voice)
{
  // The libpiper reports the broken voice files and the onnxruntime failures
  // with the exceptions.
  try {
    if (!load(voice)) {
      return {};
    }

    if (piper_synthesize_start(msynthesizer.get(), text.c_str(), nullptr) !=
        PIPER_OK) {
      LOGE("Fail to start the speech synthesis with the " << voice
                                                          << " Piper voice");
      return {};
    }

    tts::Speech::samples pcm;
    piper_audio_chunk chunk{};
    int status{PIPER_OK};

    // Every call gives the next chunk, the last one comes with the PIPER_DONE.
    do {
      status = piper_synthesize_next(msynthesizer.get(), &chunk);

      std::transform(chunk.samples, chunk.samples + chunk.num_samples,
                     std::back_inserter(pcm), to_pcm);
    } while (status == PIPER_OK);

    if (status != PIPER_DONE) {
      LOGE("Fail to synthesize the speech with the " << voice
                                                     << " Piper voice");
      return {};
    }

    LOGD("Synthesized " << pcm.size() << " samples with the " << voice
                        << " Piper voice");

    return tts::Speech{std::move(pcm), chunk.sample_rate};
  }
  catch (const std::exception& error) {
    LOGE("The Piper fails with the " << voice << " voice: " << error.what());
    return {};
  }
}

}  // namespace pipertts

namespace tts
{

ISpeechSynthesizerPtr ISpeechSynthesizer::create()
{
  return std::make_shared<pipertts::PiperController>();
}

}  // namespace tts
