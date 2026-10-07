#include "src/DarknetXX/DarknetXXController.h"

#include <src/darknet-adaptor/adaptors/ANetworkAdaptor/ANetworkAdaptor.h>
#include <src/darknet-adaptor/adaptors/NetworksLoaders/OrigDefaultLoader/OrigDefaultLoader.h>
#include <src/darknet-adaptor/adaptors/NetworksLoaders/dxxwjz1/v1/Dxxwjz1Reader.h>
#include <src/darknet-adaptor/adaptors/NetworksLoaders/original-weights/OrigWeightsReader.h>
#include <src/darknet-adaptor/adaptors/NetworksLoaders/original-weights/OrigWeightsValidator.h>
#include <src/darknet.h>
#include <src/log/log.h>

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <utility>
#include <vector>

#include "src/DarknetXX/DarknetImage.h"
#include "src/DarknetXX/Detection.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"

namespace darknetxxi
{

namespace
{

using darknet_adaptor::loaders::OrigDefaultLoader;
using darknet_adaptor::loaders::OrigWeightsReader;
using darknet_adaptor::loaders::OrigWeightsValidator;
using darknet_adaptor::loaders::dxxwjz1::v1::Dxxwjz1Reader;

/// @brief The last detection layer of the network, the way the darknetxx
/// detector picks it, or the last layer of a network of none.
const layer& detection_layer(const network& net)
{
  const layer* found = &net.layers[net.n - 1];

  for (int index = 0; index < net.n; ++index) {
    const LAYER_TYPE type = net.layers[index].type;

    if (type == YOLO || type == GAUSSIAN_YOLO || type == REGION) {
      found = &net.layers[index];
    }
  }

  return *found;
}

/// @brief The pixels box of the relative one of the center and the size,
/// clamped to the image the way the Darknet draws it.
Detection make_detection(std::string name, const float probability,
                         const box& bbox, const int width, const int height)
{
  static constexpr const float HALF = 0.5F;

  const auto pixel = [](const float position, const int size) {
    return std::clamp(static_cast<int>(position * static_cast<float>(size)), 0,
                      size - 1);
  };

  const int left = pixel(bbox.x - (bbox.w * HALF), width);
  const int top = pixel(bbox.y - (bbox.h * HALF), height);

  return {std::move(name),
          probability,
          left,
          top,
          pixel(bbox.x + (bbox.w * HALF), width) - left,
          pixel(bbox.y + (bbox.h * HALF), height) - top};
}

}  // namespace

bool DarknetXXController::init(const std::string& cfg,
                               const NetworkWeights& weights,
                               const std::string& names)
{
  mnetwork.reset();
  mnames.clear();

  std::ifstream namesFile{names};

  if (!names.empty() && !namesFile.is_open()) {
    LOGE("Fail to open the class names file: " << names);
    return false;
  }

  for (std::string name; std::getline(namesFile, name);) {
    if (!name.empty() && name.back() == '\r') {
      name.pop_back();
    }

    mnames.push_back(name);
  }

  try {
    // the single image batch inference network
    mnetwork = OrigDefaultLoader{}.parse_network_cfg_custom(cfg, 1, 1);
  }
  catch (const std::exception& error) {
    LOGE("Fail to load the network cfg file " << cfg << ": " << error.what());
    return false;
  }

  if (!weights.load_into(*this)) {
    LOGE("Fail to load the network weights file: " << weights.path());
    mnetwork.reset();
    return false;
  }

  mnetwork->fuse_conv_batchnorm();
  mnetwork->calculate_binary_weights();

  return true;
}

DarknetXXController::detections DarknetXXController::detect(
    const std::string& image)
{
  if (mnetwork == nullptr) {
    LOGE("No network loaded to detect the objects with");
    return {};
  }

  const cv::Mat bgr = cv::imread(image, cv::IMREAD_COLOR);

  if (bgr.empty()) {
    LOGE("Fail to read the image: " << image);
    return {};
  }

  network& net = *mnetwork->get();
  const DarknetImage input =
      DarknetImage{bgr}.resized(net.w, net.h, net.letter_box != 0);

  network_predict(net, input.get().data);

  int count = 0;

  const auto release = [&count](detection* const boxes) {
    free_detections(boxes, count);
  };

  const std::unique_ptr<detection, decltype(release)> found{
      get_network_boxes(&net, bgr.cols, bgr.rows, THRESHOLD,
                        HIERARCHY_THRESHOLD, nullptr, 1, &count,
                        net.letter_box),
      release};

  const layer& detector = detection_layer(net);

  if (detector.nms_kind == DEFAULT_NMS) {
    do_nms_sort(found.get(), count, detector.classes, NMS_THRESHOLD);
  } else {
    diounms_sort(found.get(), count, detector.classes, NMS_THRESHOLD,
                 detector.nms_kind, detector.beta_nms);
  }

  std::vector<Detection> objects;

  for (int index = 0; index < count; ++index) {
    const detection& candidate = found.get()[index];

    for (int kind = 0; kind < candidate.classes; ++kind) {
      if (candidate.prob[kind] > THRESHOLD) {
        const auto named = static_cast<std::size_t>(kind) < mnames.size();

        objects.push_back(make_detection(
            named ? mnames[static_cast<std::size_t>(kind)]
                  : "class " + std::to_string(kind),
            candidate.prob[kind], candidate.bbox, bgr.cols, bgr.rows));
      }
    }
  }

  return objects;
}

DarknetXXController::DarknetXXControllerPtr DarknetXXController::create()
{
  return std::make_shared<DarknetXXController>();
}

bool DarknetXXController::load(const OrigWeights& weights)
{
  // the file keeps no structure of it's own, so a file of another network or
  // of another format gets told by it's size and it's header alone
  const auto report =
      OrigWeightsValidator::validate(weights.path(), *mnetwork->get());

  report.log(weights.path());

  return report.ok() &&
         OrigWeightsReader{}.load(*mnetwork->get(), weights.path());
}

bool DarknetXXController::load(const Dxxwjz1Weights& weights)
{
  return Dxxwjz1Reader{}.load(*mnetwork->get(), weights.path());
}

}  // namespace darknetxxi
