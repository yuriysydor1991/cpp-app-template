#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>

#include "src/ONNX/ONNXModel.h"

using namespace onnxi;
using namespace testing;

class UTEST_ONNXModel : public Test
{
 public:
  ONNXModel model;
};

TEST_F(UTEST_ONNXModel, missing_model_fails_to_load)
{
  EXPECT_FALSE(model.load("no-such-model.onnx"));
  EXPECT_TRUE(model.input_shape().empty());
}

TEST_F(UTEST_ONNXModel, nothing_runs_before_the_load)
{
  cv::Mat input(2, 2, CV_32F, cv::Scalar::all(1));

  EXPECT_TRUE(model.run(input).empty());
}

TEST_F(UTEST_ONNXModel, planar_tensor_holds_the_channels_one_after_another)
{
  const cv::Mat image(2, 3, CV_32FC3, cv::Scalar(1.0F, 2.0F, 3.0F));
  const cv::Mat tensor = ONNXModel::planar(image);

  ASSERT_EQ(tensor.dims, 4);
  EXPECT_EQ(tensor.size[0], 1);
  EXPECT_EQ(tensor.size[1], 3);
  EXPECT_EQ(tensor.size[2], 2);
  EXPECT_EQ(tensor.size[3], 3);

  for (int channel = 0; channel < 3; ++channel) {
    const float* plane = tensor.ptr<float>(0, channel);

    for (int index = 0; index < 6; ++index) {
      EXPECT_FLOAT_EQ(plane[index], static_cast<float>(channel + 1));
    }
  }
}
