#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADER_CLASS_H

namespace darknetxxi
{

class OrigWeights;
class Dxxwjz1Weights;

/**
 * @brief The interface of the loaders of the network weights files. A
 * NetworkWeights file calls the method of it's own format (see the
 * NetworkWeights::load_into method), so no value tells the formats apart.
 * A new format adds it's NetworkWeights class and the method here.
 */
class WeightsLoader
{
 public:
  virtual ~WeightsLoader() = default;
  WeightsLoader() = default;

  /// @brief Loads the original Darknet weights file.
  virtual bool load(const OrigWeights& weights) = 0;

  /// @brief Loads the darknetxx dxxwjz1 weights file.
  virtual bool load(const Dxxwjz1Weights& weights) = 0;
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADER_CLASS_H
