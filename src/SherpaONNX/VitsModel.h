#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_VITSMODEL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_VITSMODEL_CLASS_H

#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>

#include "src/SherpaONNX/SherpaONNXModel.h"

namespace sherpaonnx
{

/**
 * @brief The VITS model (the vits-piper-*, the vits-melo-tts-* ones etc.):
 * the network, the tokens.txt and either the espeak-ng-data of the Piper
 * voices or the lexicon.txt of the MeloTTS ones.
 */
class VitsModel : public SherpaONNXModel
{
 public:
  /// @brief Keeps the directory of the VITS model files.
  explicit VitsModel(std::filesystem::path directory);

 protected:
  void configure_model(
      sherpa_onnx::cxx::OfflineTtsModelConfig& config) const override;
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_VITSMODEL_CLASS_H
