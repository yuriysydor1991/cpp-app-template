#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/opencv/OpenCVController.h"

using namespace opencvi;
using namespace testing;

class CTEST_opencv : public Test
{
 public:
  CTEST_opencv()
      : controller{OpenCVController::create()},
        ctx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
  }

  ~CTEST_opencv() override
  {
    std::error_code ec;
    if (!fixturePath.empty()) {
      std::filesystem::remove(fixturePath, ec);
    }
  }

  std::string make_blank_fixture(const std::string& filename)
  {
    fixturePath = (std::filesystem::temp_directory_path() / filename).string();
    cv::Mat blank(120, 120, CV_8UC3, cv::Scalar::all(0));
    cv::imwrite(fixturePath, blank);
    return fixturePath;
  }

  int argc{0};
  char** argv{nullptr};

  OpenCVController::OpenCVControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
  std::string fixturePath;
};

TEST_F(CTEST_opencv, create_default_controller_success)
{
  EXPECT_NE(controller, nullptr);
}

TEST_F(CTEST_opencv, default_cascade_path_or_skip)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  EXPECT_TRUE(controller->load_cascade());
  EXPECT_FALSE(controller->get_cascade_path().empty());
}

TEST_F(CTEST_opencv, detects_zero_faces_on_blank_image)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  ASSERT_TRUE(controller->load_cascade());

  const std::string path = make_blank_fixture("opencv-blank-fixture.png");

  const auto faces = controller->detect(path);

  EXPECT_TRUE(faces.empty());
}

TEST_F(CTEST_opencv, detect_on_missing_image_returns_empty)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  ASSERT_TRUE(controller->load_cascade());

  const auto faces =
      controller->detect(std::string{"/tmp/non-existent-image-fixture.png"});

  EXPECT_TRUE(faces.empty());
}

TEST_F(CTEST_opencv, run_loads_cascade_and_scans_image)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  ctx->image_path = make_blank_fixture("opencv-run-blank-fixture.png");

  EXPECT_TRUE(controller->run(ctx));
  EXPECT_FALSE(controller->get_cascade_path().empty());
}

TEST_F(CTEST_opencv, face_recognition_example_succeeds_without_image)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  EXPECT_TRUE(controller->face_recognition_example(ctx));
  EXPECT_FALSE(controller->get_cascade_path().empty());
}
