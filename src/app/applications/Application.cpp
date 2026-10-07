#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/DarknetXX/DarknetXXController.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/Dxxwjz2Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"
#include "src/app/CMDParamNames.h"
#include "src/log/log.h"

namespace app
{

namespace
{

/// @brief The command line value, or the given default one while the command
/// line carries none.
std::string or_default(const std::string& value, const std::string& fallback)
{
  return value.empty() ? fallback : value;
}

/// @brief The weights file of the command line, the default original one
/// while it carries none and nothing while it carries more of them.
darknetxxi::NetworkWeightsPtr weights_of(const ApplicationContext& ctx)
{
  std::vector<darknetxxi::NetworkWeightsPtr> given;

  if (!ctx.get_weights_path().empty()) {
    given.push_back(
        std::make_shared<darknetxxi::OrigWeights>(ctx.get_weights_path()));
  }

  if (!ctx.get_dxxwjz1_path().empty()) {
    given.push_back(
        std::make_shared<darknetxxi::Dxxwjz1Weights>(ctx.get_dxxwjz1_path()));
  }

  if (!ctx.get_dxxwjz2_path().empty()) {
    given.push_back(
        std::make_shared<darknetxxi::Dxxwjz2Weights>(ctx.get_dxxwjz2_path()));
  }

  if (given.empty()) {
    return std::make_shared<darknetxxi::OrigWeights>(
        project_decls::PROJECT_DARKNETXX_WEIGHTS_PATH);
  }

  return given.size() == 1U ? given.front() : nullptr;
}

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  const darknetxxi::NetworkWeightsPtr weights = weights_of(*ctx);

  if (weights == nullptr) {
    LOGE("Give either the " << CMDParamNames::WEIGHTSW << ", the "
                            << CMDParamNames::DXXWJZ1W << " or the "
                            << CMDParamNames::DXXWJZ2W
                            << " weights file, not more of them");
    return INVALID;
  }

  // The dxxwjz2 file keeps the network and the class names of it's own,
  // which the cfg and the class names files of the command line go over.
  const std::string& dxxwjz2 = ctx->get_dxxwjz2_path();
  const std::string cfg = or_default(
      ctx->get_cfg_path(),
      or_default(dxxwjz2, project_decls::PROJECT_DARKNETXX_CFG_PATH));
  const std::string names =
      dxxwjz2.empty() ? or_default(ctx->get_names_path(),
                                   project_decls::PROJECT_DARKNETXX_NAMES_PATH)
                      : ctx->get_names_path();

  auto darknetxx = darknetxxi::DarknetXXController::create();

  assert(darknetxx != nullptr);

  if (!darknetxx->init(cfg, *weights, names)) {
    LOGE("Fail to load the network, point at it with the "
         << CMDParamNames::CFGW << " and the " << CMDParamNames::WEIGHTSW
         << " or the " << CMDParamNames::DXXWJZ1W
         << " <path> command line parameters, or with the "
         << CMDParamNames::DXXWJZ2W << " <path> one");
    return INVALID;
  }

  const std::string image = or_default(
      ctx->get_image_path(), project_decls::PROJECT_DARKNETXX_IMAGE_PATH);

  const auto objects = darknetxx->detect(image);

  if (!objects.has_value()) {
    LOGE("Fail to detect the objects, point at an image with the "
         << CMDParamNames::IMAGEW << " <path> command line parameter");
    return INVALID;
  }

  LOGI("Detected " << objects->size() << " object(s) in the " << image);

  // Insert your handling of the detected objects here.
  for (const auto& object : *objects) {
    LOGI(object);
  }

  return 0;
}

}  // namespace app
