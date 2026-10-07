#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ1WEIGHTS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ1WEIGHTS_CLASS_H

#include "src/DarknetXX/weights/NetworkWeights.h"

namespace darknetxxi
{

/**
 * @brief The darknetxx dxxwjz1 weights file (*.dxxwjz1): the gzip compressed
 * JSON document of the network layers arrays, the arrays found by their
 * layers and names. Converts to the original weights file with no loss.
 */
class Dxxwjz1Weights : public NetworkWeights
{
 public:
  using NetworkWeights::NetworkWeights;

  bool load_into(WeightsLoader& loader) const override;
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ1WEIGHTS_CLASS_H
