#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#include <memory>
#include <string>
#include <vector>

#include "src/app/ApplicationContext.h"

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
  using appctx = std::shared_ptr<app::ApplicationContext>;

  virtual ~OpenCVController() = default;
  OpenCVController();
  OpenCVController(const OpenCVController&) = delete;
  OpenCVController(OpenCVController&&) = delete;

  /**
   * @brief The OpenCV controller dispatcher. Acts as the single entry
   * point for the App::run delegation so that the available examples
   * can be switched without touching the app component.
   *
   * @param ctx Filled application context to forward to the picked
   *        example. Must not be null.
   *
   * @return true on success, false if the chosen example reported a
   *         failure or the context was invalid.
   */
  virtual bool run(appctx ctx);

  /**
   * @brief Factory entry point that constructs a default-initialised
   * OpenCVController instance wrapped into the shared pointer alias
   * OpenCVControllerPtr. Preferred over directly calling the
   * constructor so that the ownership semantics stay consistent
   * across the codebase and so that the existing call sites keep
   * working when the underlying allocation strategy changes.
   *
   * @return A non-null shared pointer to the freshly created
   *         controller.
   */
  static OpenCVControllerPtr create();

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
   * @brief Loads the Haar cascade declared by the application context
   * and, when an input image is provided, runs the OpenCV face
   * detector against it. Kept as a self-contained example so that
   * additional examples can be added next to it.
   *
   * @param ctx Filled application context with the optional
   *        `cascade_path` and `image_path` fields.
   *
   * @return true when the cascade was loaded and (optionally) the
   *         detection ran to completion, false otherwise.
   */
  virtual bool face_recognition_example(appctx ctx);

  /**
   * @brief Returns the first cascade path candidate found on the
   * filesystem out of the well-known system-wide install locations.
   *
   * Empty string is returned if no candidate exists.
   */
  static std::string default_cascade_path();

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
