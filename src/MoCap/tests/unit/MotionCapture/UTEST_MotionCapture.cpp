#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <opencv2/core.hpp>

#include "src/MoCap/FrameSource.h"
#include "src/MoCap/IPoseEstimator.h"
#include "src/MoCap/MotionCapture.h"
#include "src/MoCap/tests/mocks/IPoseEstimator/IPoseEstimatorMock.h"

using namespace mocap;
using namespace testing;

namespace mocap
{

IPoseEstimatorPtr IPoseEstimator::create()
{
  return std::make_shared<NiceMock<IPoseEstimatorMock>>();
}

}  // namespace mocap

/**
 * @brief Unit test of the MotionCapture over the mocked FrameSource and
 * IPoseEstimator.
 */
class UTEST_MotionCapture : public Test
{
 public:
  using poses = IPoseEstimator::poses;

  inline static constexpr const char* const MODEL = "a-model";
  inline static constexpr const char* const INPUT = "an-input";

  const std::shared_ptr<NiceMock<IPoseEstimatorMock>> estimator{
      std::make_shared<NiceMock<IPoseEstimatorMock>>()};
  const std::shared_ptr<NiceMock<FrameSource>> source{
      std::make_shared<NiceMock<FrameSource>>()};

  MotionCapture capture{estimator, source};
};

TEST_F(UTEST_MotionCapture, create_gives_an_instance)
{
  EXPECT_NE(MotionCapture::create(), nullptr);
}

TEST_F(UTEST_MotionCapture, init_loads_the_model_of_the_estimator)
{
  EXPECT_CALL(*estimator, init(MODEL)).WillOnce(Return(true));

  EXPECT_TRUE(capture.init(MODEL));
}

TEST_F(UTEST_MotionCapture, init_failure_is_reported)
{
  EXPECT_CALL(*estimator, init(MODEL)).WillOnce(Return(false));

  EXPECT_FALSE(capture.init(MODEL));
}

TEST_F(UTEST_MotionCapture, open_opens_the_input_of_the_source)
{
  EXPECT_CALL(*source, open(INPUT)).WillOnce(Return(true));

  EXPECT_TRUE(capture.open(INPUT));
}

TEST_F(UTEST_MotionCapture, open_failure_is_reported)
{
  EXPECT_CALL(*source, open(INPUT)).WillOnce(Return(false));

  EXPECT_FALSE(capture.open(INPUT));
}

TEST_F(UTEST_MotionCapture, end_of_the_input_gives_nothing)
{
  EXPECT_CALL(*source, read(_)).WillOnce(Return(false));
  EXPECT_CALL(*estimator, estimate(_)).Times(0);

  EXPECT_FALSE(capture.capture().has_value());
}

TEST_F(UTEST_MotionCapture, estimates_the_poses_of_the_read_frame)
{
  const cv::Mat frame(4, 6, CV_8UC3, cv::Scalar::all(7));
  const poses estimated{{{cv::Point3f{1.0F, 2.0F, 0.0F}, 0.5F}}};

  EXPECT_CALL(*source, read(_))
      .WillOnce(DoAll(SetArgReferee<0>(frame), Return(true)));
  EXPECT_CALL(*estimator, estimate(_))
      .WillOnce(Invoke([&](const cv::Mat& given) {
        EXPECT_EQ(given.data, frame.data);
        return estimated;
      }));

  const auto result = capture.capture();

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, estimated);
}

TEST_F(UTEST_MotionCapture, estimation_failure_gives_nothing)
{
  EXPECT_CALL(*source, read(_)).WillOnce(Return(true));
  EXPECT_CALL(*estimator, estimate(_))
      .WillOnce(Return(IPoseEstimator::result{}));

  EXPECT_FALSE(capture.capture().has_value());
}
