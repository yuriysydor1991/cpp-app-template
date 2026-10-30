#include "src/SherpaONNX/SherpaONNXController.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <system_error>
#include <thread>
#include <utility>

#include "src/STT/ISpeechRecognizer.h"
#include "src/log/log.h"

namespace sherpaonnx
{

namespace
{

/**
 * @brief Gives the given network of the model directory: the <name>.onnx file
 * or the quantized <name>.int8.onnx one, an empty path if there is none.
 */
std::string network(const std::filesystem::path& directory,
                    const std::string& name)
{
  std::error_code error;

  for (const auto& file : {name + ".onnx", name + ".int8.onnx"}) {
    if (std::filesystem::is_regular_file(directory / file, error)) {
      return (directory / file).string();
    }
  }

  return {};
}

/// @brief Configures the sherpa-onnx with the NeMo transducer model files of
/// the given directory. The given model type spares the sherpa-onnx a load of
/// the encoder for the type of it's metadata.
sherpa_onnx::cxx::OfflineRecognizerConfig configure(
    const std::filesystem::path& directory)
{
  sherpa_onnx::cxx::OfflineRecognizerConfig config;
  auto& model = config.model_config;

  model.transducer.encoder = network(directory, "encoder");
  model.transducer.decoder = network(directory, "decoder");
  model.transducer.joiner = network(directory, "joiner");
  model.tokens = (directory / "tokens.txt").string();
  model.model_type = "nemo_transducer";
  model.num_threads = static_cast<std::int32_t>(
      std::max(1U, std::thread::hardware_concurrency()));

  return config;
}

/// @brief Strips the spaces the text of the recognized tokens starts with.
std::string trimmed(const std::string& text)
{
  const auto first = text.find_first_not_of(' ');

  return first == std::string::npos
             ? std::string{}
             : text.substr(first, text.find_last_not_of(' ') - first + 1U);
}

}  // namespace

bool SherpaONNXController::init(const std::string& model)
{
  mrecognizer.reset();

  auto recognizer =
      sherpa_onnx::cxx::OfflineRecognizer::Create(configure(model));

  if (recognizer.Get() == nullptr) {
    LOGE("Fail to load the sherpa-onnx NeMo transducer model of the "
         << model
         << " directory, unpack one of the sherpa-onnx asr-models release "
            "archives there");
    return false;
  }

  mrecognizer.emplace(std::move(recognizer));

  LOGD("The sherpa-onnx model of the " << model << " directory is loaded");

  return true;
}

SherpaONNXController::result SherpaONNXController::recognize(
    const samples& audio)
{
  if (!mrecognizer.has_value()) {
    LOGE("The sherpa-onnx recognizer has no model loaded");
    return {};
  }

  const auto stream = mrecognizer->CreateStream();

  stream.AcceptWaveform(SAMPLE_RATE, audio.data(),
                        static_cast<std::int32_t>(audio.size()));
  mrecognizer->Decode(&stream);

  return trimmed(mrecognizer->GetResult(&stream).text);
}

}  // namespace sherpaonnx

namespace stt
{

ISpeechRecognizerPtr ISpeechRecognizer::create()
{
  return std::make_shared<sherpaonnx::SherpaONNXController>();
}

}  // namespace stt
