#include "src/MoCap/MotionCapture.h"

#include <memory>
#include <string>
#include <utility>

namespace mocap
{

MotionCapture::MotionCapture(IPoseEstimatorPtr estimator, FrameSourcePtr source)
    : mestimator{std::move(estimator)}, msource{std::move(source)}
{
}

bool MotionCapture::init(const std::string& model)
{
  return mestimator->init(model);
}

bool MotionCapture::open(const std::string& input)
{
  return msource->open(input);
}

MotionCapture::result MotionCapture::capture()
{
  if (!msource->read(mframe)) {
    return {};
  }

  return mestimator->estimate(mframe);
}

MotionCapturePtr MotionCapture::create()
{
  return std::make_shared<MotionCapture>(IPoseEstimator::create(),
                                         FrameSource::create());
}

}  // namespace mocap
