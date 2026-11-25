#include "src/app/applications/Application.h"

#include <cassert>
#include <cstddef>
#include <memory>
#include <sstream>
#include <string>

#include "project-global-decls.h"
#include "src/MoCap/MotionCapture.h"
#include "src/app/CMDParamNames.h"
#include "src/app/DataLocator.h"
#include "src/log/log.h"

namespace app
{

int Application::run(ApplicationContextPtr ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  const std::string model =
      ctx->get_model_path().empty()
          ? DataLocator::locate(project_decls::PROJECT_POSE_MODEL)
          : ctx->get_model_path();
  const std::string input = ctx->get_input().empty()
                                ? CMDParamNames::DEFAULT_INPUT
                                : ctx->get_input();

  auto capture = mocap::MotionCapture::create();

  assert(capture != nullptr);

  if (!capture->init(model)) {
    LOGE("Fail to load the pose estimation model, point at one with the "
         << CMDParamNames::MODELW << " or " << CMDParamNames::MODEL
         << " <path> command line parameter");
    return INVALID;
  }

  if (!capture->open(input)) {
    LOGE(
        "Fail to open the input, give a camera index, an image or a video "
        "with the "
        << CMDParamNames::INPUTW << " or " << CMDParamNames::INPUT
        << " <input> command line parameter");
    return INVALID;
  }

  LOGI("Capturing the body motion of the " << input
                                           << " input, press Ctrl+C to stop");

  // Insert your handling of the captured poses here.
  for (std::size_t frame = 0; !ctx->get_stop(); ++frame) {
    const auto poses = capture->capture();

    if (!poses.has_value()) {
      break;
    }

    for (const auto& pose : *poses) {
      std::ostringstream keypoints;

      for (const auto& [position, score] : pose) {
        keypoints << ' ' << position << ' ' << score;
      }

      LOGI("Frame " << frame << " pose:" << keypoints.str());
    }
  }

  return 0;
}

}  // namespace app
