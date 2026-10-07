#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ORIGWEIGHTS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ORIGWEIGHTS_CLASS_H

#include "src/DarknetXX/weights/NetworkWeights.h"

namespace darknetxxi
{

/**
 * @brief The original Darknet weights file (*.weights): the binary arrays of
 * the network layers, which only the network cfg file gives the structure.
 */
class OrigWeights : public NetworkWeights
{
 public:
  using NetworkWeights::NetworkWeights;

  bool load_into(WeightsLoader& loader) const override;
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ORIGWEIGHTS_CLASS_H
