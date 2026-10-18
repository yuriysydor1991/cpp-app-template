#include "src/SherpaONNX/VitsModel.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <utility>

#include "src/SherpaONNX/SherpaONNXModel.h"

namespace sherpaonnx
{

VitsModel::VitsModel(std::filesystem::path directory)
    : SherpaONNXModel{std::move(directory)}
{
}

void VitsModel::configure_model(
    sherpa_onnx::cxx::OfflineTtsModelConfig& config) const
{
  config.vits.model = network();
  config.vits.tokens = existing({"tokens.txt"});
  config.vits.data_dir = existing({"espeak-ng-data"});
  config.vits.lexicon = existing({"lexicon.txt"});
}

}  // namespace sherpaonnx
