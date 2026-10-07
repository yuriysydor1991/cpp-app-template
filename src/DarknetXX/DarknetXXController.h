#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "src/DarknetXX/Detection.h"
#include "src/DarknetXX/weights/NetworkWeights.h"
#include "src/DarknetXX/weights/WeightsLoader.h"

namespace darknet_adaptor::adaptors
{
class ANetworkAdaptor;
}  // namespace darknet_adaptor::adaptors

/**
 * @brief The darknetxx object detection adaptor subsystem namespace.
 */
namespace darknetxxi
{

/**
 * @brief The darknetxx object detection controller. It loads a Darknet
 * network of the cfg file with the weights of any format the darknetxx reads
 * and detects the objects in the images with it.
 *
 * The header keeps the darknetxx headers out, so the project sources include
 * it the usual way, while it's implementation compiles with the darknetxx
 * include directories first (see the src/DarknetXX/CMakeLists.txt). The
 * darknetxx messages go into the project logger. Nothing throws: the failures
 * are logged and reported through the return values.
 */
class DarknetXXController : private WeightsLoader
{
 public:
  using detections = std::optional<std::vector<Detection>>;
  using DarknetXXControllerPtr = std::shared_ptr<DarknetXXController>;

  ~DarknetXXController() override = default;
  DarknetXXController() = default;

  /**
   * @brief Loads the network in place of the previously loaded one.
   *
   * @param cfg The network cfg file path, e.g. the yolov4-tiny.cfg one.
   * @param weights The weights file of the network.
   * @param names The class names file path, a name per line (e.g. the
   * coco.names one), the empty one to number the classes instead.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool init(const std::string& cfg, const NetworkWeights& weights,
                    const std::string& names);

  /**
   * @brief Detects the objects in the image.
   *
   * @param image The image file path of any format the OpenCV reads.
   *
   * @return Returns the detected objects, or nothing if the controller is not
   * initialized or the image fails to read.
   */
  virtual detections detect(const std::string& image);

  /**
   * @brief Creates a controller instance. Call the DarknetXXController::init
   * method before the detection.
   *
   * @return The created controller.
   */
  static DarknetXXControllerPtr create();

  /// @brief The minimal probability of the detected objects.
  inline static constexpr const float THRESHOLD = 0.25F;

 private:
  bool load(const OrigWeights& weights) override;
  bool load(const Dxxwjz1Weights& weights) override;

  inline static constexpr const float HIERARCHY_THRESHOLD = 0.5F;
  inline static constexpr const float NMS_THRESHOLD = 0.45F;

  std::shared_ptr<darknet_adaptor::adaptors::ANetworkAdaptor> mnetwork;
  std::vector<std::string> mnames;
};

using DarknetXXControllerPtr = DarknetXXController::DarknetXXControllerPtr;

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H
