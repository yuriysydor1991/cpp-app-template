#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KOKOROMODEL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KOKOROMODEL_CLASS_H

#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>

#include "src/SherpaONNX/SherpaONNXModel.h"

namespace sherpaonnx
{

/**
 * @brief The Kokoro model (the kokoro-int8-multi-lang-v1_0, the
 * kokoro-en-v0_19 one etc.): the network, the voices.bin speakers, the
 * tokens.txt, the espeak-ng-data and, for the multilingual models, the
 * American English and the Chinese lexicons.
 */
class KokoroModel : public SherpaONNXModel
{
 public:
  /// @brief Keeps the directory of the Kokoro model files.
  explicit KokoroModel(std::filesystem::path directory);

 protected:
  void configure_model(
      sherpa_onnx::cxx::OfflineTtsModelConfig& config) const override;
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KOKOROMODEL_CLASS_H
