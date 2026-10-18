#include "src/SherpaONNX/SherpaONNXModel.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <initializer_list>
#include <memory>
#include <string>
#include <system_error>
#include <thread>
#include <utility>

#include "src/SherpaONNX/KokoroModel.h"
#include "src/SherpaONNX/VitsModel.h"

namespace sherpaonnx
{

SherpaONNXModel::SherpaONNXModel(std::filesystem::path directory)
    : mdirectory{std::move(directory)}
{
}

SherpaONNXModelPtr SherpaONNXModel::detect(
    const std::filesystem::path& directory)
{
  std::error_code error;

  if (std::filesystem::is_regular_file(directory / "voices.bin", error)) {
    return std::make_unique<KokoroModel>(directory);
  }

  if (std::filesystem::is_regular_file(directory / "tokens.txt", error)) {
    return std::make_unique<VitsModel>(directory);
  }

  return nullptr;
}

sherpa_onnx::cxx::OfflineTtsConfig SherpaONNXModel::configure() const
{
  sherpa_onnx::cxx::OfflineTtsConfig config;

  config.model.num_threads = static_cast<std::int32_t>(
      std::max(1U, std::thread::hardware_concurrency()));

  configure_model(config.model);

  return config;
}

std::string SherpaONNXModel::network() const
{
  // The model.onnx goes first, since an archive may keep a mere git-lfs
  // pointer by the model.int8.onnx name next to it.
  for (const char* const name : {"model.onnx", "model.int8.onnx"}) {
    std::string path = existing({name});

    if (!path.empty()) {
      return path;
    }
  }

  std::error_code error;

  for (const auto& entry :
       std::filesystem::directory_iterator{mdirectory, error}) {
    if (entry.path().extension() == ".onnx") {
      return entry.path().string();
    }
  }

  return {};
}

std::string SherpaONNXModel::existing(
    const std::initializer_list<const char*> names) const
{
  std::string paths;
  std::error_code error;

  for (const char* const name : names) {
    if (std::filesystem::exists(mdirectory / name, error)) {
      paths += (paths.empty() ? "" : ",") + (mdirectory / name).string();
    }
  }

  return paths;
}

}  // namespace sherpaonnx
