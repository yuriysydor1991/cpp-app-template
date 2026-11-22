#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATORMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATORMOCK_CLASS_H

#include <gmock/gmock.h>

#include <opencv2/core.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"

namespace mocap
{

class IPoseEstimatorMock : public IPoseEstimator
{
 public:
  IPoseEstimatorMock()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, estimate(_)).WillByDefault(Return(result{poses{}}));
  }

  MOCK_METHOD(bool, init, (const std::string& model), (override));
  MOCK_METHOD(result, estimate, (const cv::Mat& frame), (override));
};

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATORMOCK_CLASS_H
