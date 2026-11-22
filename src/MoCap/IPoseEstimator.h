#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATOR_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATOR_CLASS_H

#include <memory>
#include <opencv2/core.hpp>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief The engine neutral body motion capture subsystem namespace.
 */
namespace mocap
{

/**
 * @brief The interface every pose estimation engine of the project
 * implements: it loads a model and estimates the body poses of a frame.
 *
 * The engines report their failures through the return values and the
 * project log instead of throwing.
 */
class IPoseEstimator
{
 public:
  /// @brief The keypoint position in the frame pixels with the depth of the
  /// 3D models (zero for the 2D ones) and the keypoint score.
  using keypoint = std::tuple<cv::Point3f, float>;
  /// @brief The keypoints of a body in the keypoints order of the model.
  using pose = std::vector<keypoint>;
  using poses = std::vector<pose>;
  using result = std::optional<poses>;
  using IPoseEstimatorPtr = std::shared_ptr<IPoseEstimator>;

  virtual ~IPoseEstimator() = default;
  IPoseEstimator() = default;
  IPoseEstimator(const IPoseEstimator&) = delete;
  IPoseEstimator& operator=(const IPoseEstimator&) = delete;

  /**
   * @brief Loads the model in place of the previously loaded one.
   *
   * @param model The model of the engine: a file or a directory, whatever
   * the engine keeps it's models in.
   */
  virtual bool init(const std::string& model) = 0;

  /**
   * @brief Estimates the poses of the bodies the frame shows.
   *
   * @param frame The BGR image.
   *
   * @return The poses, the empty ones for no body, or nothing if no model is
   * loaded or the estimation fails.
   */
  virtual result estimate(const cv::Mat& frame) = 0;

  /**
   * @brief Creates the estimator of the engine the build links in. The
   * engine sources of the flavor define it, so swapping the engine leaves the
   * callers untouched.
   */
  static IPoseEstimatorPtr create();
};

using IPoseEstimatorPtr = IPoseEstimator::IPoseEstimatorPtr;

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IPOSEESTIMATOR_CLASS_H
