#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>

#include "src/DarknetXX/DarknetImage.h"

using namespace darknetxxi;
using namespace testing;

/**
 * @brief Unit test of the DarknetImage over the Darknet image routines of the
 * darknetxx core.
 */
class UTEST_DarknetImage : public Test
{
 public:
  /// @brief The image of the plain red and green planes and the blue one
  /// growing from the left to the right.
  static cv::Mat bgr()
  {
    cv::Mat pixels(HEIGHT, WIDTH, CV_8UC3);

    for (int row = 0; row < HEIGHT; ++row) {
      for (int col = 0; col < WIDTH; ++col) {
        pixels.at<cv::Vec3b>(row, col) =
            cv::Vec3b{static_cast<uchar>(BLUE_STEP * col), GREEN, RED};
      }
    }

    return pixels;
  }

  static float at(const image& planes, const int channel, const int col,
                  const int row)
  {
    return planes.data[(channel * planes.h + row) * planes.w + col];
  }

  inline static constexpr const int WIDTH = 4;
  inline static constexpr const int HEIGHT = 2;
  inline static constexpr const int BLUE_STEP = 60;
  inline static constexpr const uchar GREEN = 100U;
  inline static constexpr const uchar RED = 250U;
};

TEST_F(UTEST_DarknetImage, keeps_the_size_of_the_image)
{
  const DarknetImage converted{bgr()};

  EXPECT_EQ(converted.get().w, WIDTH);
  EXPECT_EQ(converted.get().h, HEIGHT);
  EXPECT_EQ(converted.get().c, 3);
}

TEST_F(UTEST_DarknetImage, keeps_the_red_green_blue_planes_of_the_floats)
{
  const DarknetImage converted{bgr()};

  for (int row = 0; row < HEIGHT; ++row) {
    for (int col = 0; col < WIDTH; ++col) {
      EXPECT_FLOAT_EQ(at(converted.get(), 0, col, row), RED / 255.0F);
      EXPECT_FLOAT_EQ(at(converted.get(), 1, col, row), GREEN / 255.0F);
      EXPECT_FLOAT_EQ(at(converted.get(), 2, col, row),
                      static_cast<float>(BLUE_STEP * col) / 255.0F);
    }
  }
}

TEST_F(UTEST_DarknetImage, stretches_into_the_network_input)
{
  const DarknetImage sized = DarknetImage{bgr()}.resized(8, 6, false);

  EXPECT_EQ(sized.get().w, 8);
  EXPECT_EQ(sized.get().h, 6);
  EXPECT_NEAR(at(sized.get(), 0, 0, 0), RED / 255.0F, 1e-5);
  EXPECT_NEAR(at(sized.get(), 0, 7, 5), RED / 255.0F, 1e-5);
}

TEST_F(UTEST_DarknetImage, letterboxes_into_the_network_input)
{
  const DarknetImage boxed = DarknetImage{bgr()}.resized(8, 8, true);

  EXPECT_EQ(boxed.get().w, 8);
  EXPECT_EQ(boxed.get().h, 8);

  // the image of the half the height in the middle of the gray box
  EXPECT_FLOAT_EQ(at(boxed.get(), 0, 4, 0), 0.5F);
  EXPECT_NEAR(at(boxed.get(), 0, 4, 4), RED / 255.0F, 1e-5);
  EXPECT_FLOAT_EQ(at(boxed.get(), 0, 4, 7), 0.5F);
}
