#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/opencv/OpenCVController.h"

using namespace opencvi;
using namespace testing;

class UTEST_OpenCVController : public Test
{
 public:
  UTEST_OpenCVController()
      : controller{OpenCVController::create()},
        ctx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  OpenCVController::OpenCVControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
};

TEST_F(UTEST_OpenCVController, create_success)
{
  EXPECT_NE(controller, nullptr);
  EXPECT_TRUE(controller->get_cascade_path().empty());
}

TEST_F(UTEST_OpenCVController, detect_returns_empty_when_cascade_not_loaded)
{
  cv::Mat image(64, 64, CV_8UC1, cv::Scalar::all(0));

  const auto faces = controller->detect(image);

  EXPECT_TRUE(faces.empty());
}

TEST_F(UTEST_OpenCVController, detect_with_empty_path_is_safe)
{
  const auto faces = controller->detect(std::string{});

  EXPECT_TRUE(faces.empty());
}

TEST_F(UTEST_OpenCVController, load_cascade_with_missing_file_fails)
{
  EXPECT_FALSE(controller->load_cascade("/tmp/this/path/does/not/exist.xml"));
  EXPECT_TRUE(controller->get_cascade_path().empty());
}

TEST_F(UTEST_OpenCVController, default_cascade_path_resolves_when_installed)
{
  const std::string defaultPath = OpenCVController::default_cascade_path();

  if (defaultPath.empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  std::error_code ec;
  EXPECT_TRUE(std::filesystem::exists(defaultPath, ec));
  EXPECT_FALSE(ec);
}

TEST_F(UTEST_OpenCVController, load_default_cascade_when_available)
{
  const std::string defaultPath = OpenCVController::default_cascade_path();

  if (defaultPath.empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  EXPECT_TRUE(controller->load_cascade());
  EXPECT_EQ(controller->get_cascade_path(), defaultPath);

  cv::Mat blank(120, 120, CV_8UC3, cv::Scalar::all(0));

  const auto faces = controller->detect(blank);

  EXPECT_TRUE(faces.empty());
}

TEST_F(UTEST_OpenCVController, run_with_null_context_returns_false)
{
  EXPECT_FALSE(controller->run({}));
}

TEST_F(UTEST_OpenCVController, face_recognition_example_with_null_context_returns_false)
{
  EXPECT_FALSE(controller->face_recognition_example({}));
}

TEST_F(UTEST_OpenCVController, face_recognition_example_fails_on_missing_cascade)
{
  ctx->cascade_path = "/tmp/this/path/does/not/exist.xml";

  EXPECT_FALSE(controller->face_recognition_example(ctx));
}

TEST_F(UTEST_OpenCVController, run_fails_on_missing_cascade)
{
  ctx->cascade_path = "/tmp/this/path/does/not/exist.xml";

  EXPECT_FALSE(controller->run(ctx));
}

TEST_F(UTEST_OpenCVController, face_recognition_example_succeeds_without_image)
{
  const std::string defaultPath = OpenCVController::default_cascade_path();

  if (defaultPath.empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  EXPECT_TRUE(controller->face_recognition_example(ctx));
  EXPECT_EQ(controller->get_cascade_path(), defaultPath);
}

TEST_F(UTEST_OpenCVController, run_succeeds_without_image)
{
  const std::string defaultPath = OpenCVController::default_cascade_path();

  if (defaultPath.empty()) {
    GTEST_SKIP() << "No preinstalled OpenCV Haar cascade was found on the host";
  }

  EXPECT_TRUE(controller->run(ctx));
  EXPECT_EQ(controller->get_cascade_path(), defaultPath);
}
