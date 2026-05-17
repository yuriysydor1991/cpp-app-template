#include "src/opencv/OpenCVController.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <array>
#include <cassert>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "src/log/log.h"

namespace opencvi
{

OpenCVController::OpenCVController() = default;

bool OpenCVController::load_cascade(const std::string& cascadePath)
{
  const std::string target =
      cascadePath.empty() ? default_cascade_path() : cascadePath;

  if (target.empty()) {
    LOGE("No Haar cascade XML file path was provided and no system-wide "
         "default was found");
    return false;
  }

  LOGT("Loading the Haar cascade from " << target);

  if (!cascade.load(target)) {
    LOGE("Failed to load the Haar cascade from " << target);
    loadedCascadePath.clear();
    return false;
  }

  loadedCascadePath = target;

  LOGI("Haar cascade loaded from " << target);

  return true;
}

OpenCVController::faces_buffer OpenCVController::detect(const cv::Mat& image)
{
  faces_buffer faces;

  if (cascade.empty()) {
    LOGE("Haar cascade is not loaded yet");
    return faces;
  }

  if (image.empty()) {
    LOGE("Input image is empty");
    return faces;
  }

  cv::Mat gray;

  if (image.channels() == 1) {
    gray = image;
  } else {
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  }

  cv::equalizeHist(gray, gray);

  const cv::Size minSize{DEFAULT_MIN_SIZE_PX, DEFAULT_MIN_SIZE_PX};

  cascade.detectMultiScale(gray, faces, DEFAULT_SCALE_FACTOR,
                           DEFAULT_MIN_NEIGHBORS, 0, minSize);

  LOGT("Detected " << faces.size() << " face(s)");

  return faces;
}

OpenCVController::faces_buffer OpenCVController::detect(
    const std::string& imagePath)
{
  assert(!imagePath.empty());

  if (imagePath.empty()) {
    LOGE("Empty image path");
    return {};
  }

  cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

  if (image.empty()) {
    LOGE("Failed to read the image at " << imagePath);
    return {};
  }

  return detect(image);
}

const std::string& OpenCVController::get_cascade_path() const
{
  return loadedCascadePath;
}

std::string OpenCVController::default_cascade_path()
{
  static const std::array<const char*, 6> kCandidates{{
      "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml",
      "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml",
      "/usr/local/share/opencv4/haarcascades/"
      "haarcascade_frontalface_default.xml",
      "/usr/local/share/opencv/haarcascades/"
      "haarcascade_frontalface_default.xml",
      "/usr/local/Cellar/opencv/HEAD/share/opencv4/haarcascades/"
      "haarcascade_frontalface_default.xml",
      "/opt/homebrew/share/opencv4/haarcascades/"
      "haarcascade_frontalface_default.xml",
  }};

  for (const auto* candidate : kCandidates) {
    std::error_code ec;
    if (std::filesystem::exists(candidate, ec) && !ec) {
      return candidate;
    }
  }

  return {};
}

OpenCVControllerPtr OpenCVController::create()
{
  return std::make_shared<OpenCVController>();
}

}  // namespace opencvi
