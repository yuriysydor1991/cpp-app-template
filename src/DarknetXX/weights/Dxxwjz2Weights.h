#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ2WEIGHTS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ2WEIGHTS_CLASS_H

#include "src/DarknetXX/weights/NetworkWeights.h"

namespace darknetxxi
{

/**
 * @brief The darknetxx dxxwjz2 weights file (*.dxxwjz2): the dxxwjz1 document
 * of the weights with the network they are of, the text of it's cfg file and
 * the class names, and the record of it's training. So the file alone is the
 * network to detect with.
 */
class Dxxwjz2Weights : public NetworkWeights
{
 public:
  using NetworkWeights::NetworkWeights;

  bool load_into(WeightsLoader& loader) const override;
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DXXWJZ2WEIGHTS_CLASS_H
