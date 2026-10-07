#include "src/DarknetXX/weights/OrigWeights.h"

namespace darknetxxi
{

bool OrigWeights::load_into(WeightsLoader& loader) const
{
  return loader.load(*this);
}

}  // namespace darknetxxi
