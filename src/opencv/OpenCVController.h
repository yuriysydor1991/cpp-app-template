#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#include <memory>
#include <string>
#include <vector>

/**
 * @brief The OpenCV adaptor subsystem namespace.
 */
namespace opencvi
{

/**
 * @brief Thin wrapper around the OpenCV pre-installed Haar cascade
 * face detector that ships with the system OpenCV installation
 * (`haarcascade_frontalface_default.xml`).
 *
 * The controller is intentionally minimal: it loads the cascade
 * once and offers a couple of overloads that run the detector
 * against a raw `cv::Mat` or against an on-disk image file.
 */
class OpenCVController
{
 public:
  using faces_buffer = std::vector<cv::Rect>;
  using OpenCVControllerPtr = std::shared_ptr<OpenCVController>;

  virtual ~OpenCVController() = default;
  OpenCVController();
  OpenCVController(const OpenCVController&) = delete;
  OpenCVController(OpenCVController&&) = delete;

  /**
   * @brief Loads the requested Haar cascade XML file.
   *
   * @param cascadePath Absolute path to the cascade XML. An empty
   *        string makes the method try the project's default
   *        candidates (see default_cascade_path()).
   *
   * @return true on success, false if the cascade could not be loaded.
   */
  virtual bool load_cascade(const std::string& cascadePath = {});

  /**
   * @brief Runs face detection against an already-decoded image matrix.
   *
   * @param image The input image, in any colour space supported by
   *        the OpenCV `cvtColor` BGR2GRAY conversion.
   *
   * @return Bounding rectangles around the faces that were found,
   *         empty if no face was detected or if the cascade is not
   *         yet loaded.
   */
  virtual faces_buffer detect(const cv::Mat& image);

  /**
   * @brief Convenience overload that decodes the image from disk and
   * then delegates to detect(const cv::Mat&).
   *
   * @param imagePath Absolute path to an image file readable by
   *        `cv::imread`.
   */
  virtual faces_buffer detect(const std::string& imagePath);

  /**
   * @brief Returns the currently loaded cascade path. An empty value
   * means the cascade has not been loaded yet.
   */
  virtual const std::string& get_cascade_path() const;

  /**
   * @brief Returns the first cascade path candidate found on the
   * filesystem out of the well-known system-wide install locations.
   *
   * Empty string is returned if no candidate exists.
   */
  static std::string default_cascade_path();

  static OpenCVControllerPtr create();

 private:
  inline static constexpr const double DEFAULT_SCALE_FACTOR = 1.1;
  inline static constexpr const int DEFAULT_MIN_NEIGHBORS = 3;
  inline static constexpr const int DEFAULT_MIN_SIZE_PX = 24;

  cv::CascadeClassifier cascade;
  std::string loadedCascadePath;
};

using OpenCVControllerPtr = OpenCVController::OpenCVControllerPtr;

}  // namespace opencvi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H
