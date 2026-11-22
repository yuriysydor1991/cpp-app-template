#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

#include "src/MoCap/FrameSource.h"

using namespace mocap;
using namespace testing;

/**
 * @brief Unit test of the FrameSource over the images it writes.
 */
class UTEST_FrameSource : public Test
{
 public:
  ~UTEST_FrameSource() override
  {
    std::error_code error;
    std::filesystem::remove(image, error);
  }

  const std::string image{
      (std::filesystem::temp_directory_path() /
       ("UTEST_FrameSource-" +
        std::string{UnitTest::GetInstance()->current_test_info()->name()} +
        ".png"))
          .string()};

  FrameSource source;
};

TEST_F(UTEST_FrameSource, create_gives_an_instance)
{
  EXPECT_NE(FrameSource::create(), nullptr);
}

TEST_F(UTEST_FrameSource, reads_the_single_frame_of_an_image)
{
  ASSERT_TRUE(
      cv::imwrite(image, cv::Mat(48, 64, CV_8UC3, cv::Scalar(1, 2, 3))));

  cv::Mat frame;

  ASSERT_TRUE(source.open(image));
  ASSERT_TRUE(source.read(frame));
  EXPECT_EQ(frame.size(), cv::Size(64, 48));
  EXPECT_EQ(frame.channels(), 3);
  EXPECT_FALSE(source.read(frame));
}

TEST_F(UTEST_FrameSource, missing_file_fails_to_open)
{
  EXPECT_FALSE(source.open(image));
}

TEST_F(UTEST_FrameSource, nothing_is_read_before_the_open)
{
  cv::Mat frame;

  EXPECT_FALSE(source.read(frame));
}
