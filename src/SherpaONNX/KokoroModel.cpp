#include "src/SherpaONNX/KokoroModel.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <utility>

#include "src/SherpaONNX/SherpaONNXModel.h"

namespace sherpaonnx
{

KokoroModel::KokoroModel(std::filesystem::path directory)
    : SherpaONNXModel{std::move(directory)}
{
}

void KokoroModel::configure_model(
    sherpa_onnx::cxx::OfflineTtsModelConfig& config) const
{
  config.kokoro.model = network();
  config.kokoro.voices = existing({"voices.bin"});
  config.kokoro.tokens = existing({"tokens.txt"});
  config.kokoro.data_dir = existing({"espeak-ng-data"});
  config.kokoro.lexicon = existing({"lexicon-us-en.txt", "lexicon-zh.txt"});
}

}  // namespace sherpaonnx
