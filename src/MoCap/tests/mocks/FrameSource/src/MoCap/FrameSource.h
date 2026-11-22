#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <opencv2/core.hpp>
#include <string>

namespace mocap
{

class FrameSource
{
 public:
  using FrameSourcePtr = std::shared_ptr<FrameSource>;

  virtual ~FrameSource() = default;

  FrameSource()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, open(_)).WillByDefault(Return(true));
  }

  MOCK_METHOD(bool, open, (const std::string& input));
  MOCK_METHOD(bool, read, (cv::Mat & frame));

  inline static FrameSourcePtr create()
  {
    return std::make_shared<::testing::NiceMock<FrameSource>>();
  }
};

using FrameSourcePtr = FrameSource::FrameSourcePtr;

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H
