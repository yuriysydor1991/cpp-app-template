#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

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

    for (const auto& path : fixturePaths) {
      std::filesystem::remove_all(path, ec);
    }
  }

  std::string fixture_path(const std::string& filename)
  {
    fixturePaths.emplace_back(
        (std::filesystem::temp_directory_path() / filename).string());

    return fixturePaths.back();
  }

  std::string make_blank_fixture(const std::string& filename)
  {
    const auto path = fixture_path(filename);
    const cv::Mat blank(120, 120, CV_8UC3, cv::Scalar::all(0));

    EXPECT_TRUE(cv::imwrite(path, blank));
    EXPECT_TRUE(std::filesystem::is_regular_file(path));

    return path;
  }

  std::string make_text_fixture(const std::string& filename)
  {
    const auto path = fixture_path(filename);

    std::ofstream{path} << "no image and no cascade XML at all";

    EXPECT_TRUE(std::filesystem::is_regular_file(path));

    return path;
  }

  int argc{0};
  char** argv{nullptr};

  OpenCVController::OpenCVControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
  std::vector<std::string> fixturePaths;
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

  ctx->set_image_path(make_blank_fixture("opencv-run-blank-fixture.png"));

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

TEST_F(CTEST_opencv, a_cascade_file_of_no_xml_fails_to_load_with_no_throw)
{
  const auto path = make_text_fixture("opencv-broken-cascade-fixture.xml");

  bool loaded{true};

  EXPECT_NO_THROW(loaded = controller->load_cascade(path));
  EXPECT_FALSE(loaded);
  EXPECT_TRUE(controller->get_cascade_path().empty());
}

TEST_F(CTEST_opencv, a_missing_image_fails_the_example)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  ctx->set_image_path(fixture_path("opencv-missing-image-fixture.png"));

  EXPECT_FALSE(controller->face_recognition_example(ctx));
}

TEST_F(CTEST_opencv, an_unreadable_image_fails_the_example)
{
  if (OpenCVController::default_cascade_path().empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  ctx->set_image_path(make_text_fixture("opencv-broken-image-fixture.png"));

  EXPECT_FALSE(controller->face_recognition_example(ctx));
}

TEST_F(CTEST_opencv, the_snap_cascade_goes_first)
{
  const std::filesystem::path snap{fixture_path("opencv-snap-fixture")};
  const auto cascade = snap / "usr/share/opencv4/haarcascades" /
                       "haarcascade_frontalface_default.xml";

  std::filesystem::create_directories(cascade.parent_path());
  std::ofstream{cascade} << "<opencv_storage></opencv_storage>";

  setenv("SNAP", snap.c_str(), 1);

  const auto found = OpenCVController::default_cascade_path();

  unsetenv("SNAP");

  EXPECT_EQ(found, cascade.string());
}
