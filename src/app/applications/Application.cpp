#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/DarknetXX/DarknetXXController.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
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

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  if (!ctx->get_weights_path().empty() && !ctx->get_dxxwjz1_path().empty()) {
    LOGE("Give either the " << CMDParamNames::WEIGHTSW << " or the "
                            << CMDParamNames::DXXWJZ1W
                            << " weights file, not both of them");
    return INVALID;
  }

  const darknetxxi::NetworkWeightsPtr weights =
      ctx->get_dxxwjz1_path().empty()
          ? darknetxxi::NetworkWeightsPtr{std::make_shared<
                darknetxxi::OrigWeights>(
                or_default(ctx->get_weights_path(),
                           project_decls::PROJECT_DARKNETXX_WEIGHTS_PATH))}
          : std::make_shared<darknetxxi::Dxxwjz1Weights>(
                ctx->get_dxxwjz1_path());

  auto darknetxx = darknetxxi::DarknetXXController::create();

  assert(darknetxx != nullptr);

  if (!darknetxx->init(
          or_default(ctx->get_cfg_path(),
                     project_decls::PROJECT_DARKNETXX_CFG_PATH),
          *weights,
          or_default(ctx->get_names_path(),
                     project_decls::PROJECT_DARKNETXX_NAMES_PATH))) {
    LOGE("Fail to load the network, point at it with the "
         << CMDParamNames::CFGW << " and the " << CMDParamNames::WEIGHTSW
         << " or the " << CMDParamNames::DXXWJZ1W
         << " <path> command line parameters");
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
