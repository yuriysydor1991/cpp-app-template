#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>

#include "src/MoCap/IPoseEstimator.h"

namespace mocap
{

class MotionCapture
{
 public:
  using result = IPoseEstimator::result;
  using MotionCapturePtr = std::shared_ptr<MotionCapture>;

  virtual ~MotionCapture() = default;

  MotionCapture()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, open(_)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(MotionCapture&)> onMockCreate;

  MOCK_METHOD(bool, init, (const std::string& model));
  MOCK_METHOD(bool, open, (const std::string& input));
  MOCK_METHOD(result, capture, ());

  inline static MotionCapturePtr create()
  {
    return std::make_shared<::testing::NiceMock<MotionCapture>>();
  }
};

using MotionCapturePtr = MotionCapture::MotionCapturePtr;

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H
