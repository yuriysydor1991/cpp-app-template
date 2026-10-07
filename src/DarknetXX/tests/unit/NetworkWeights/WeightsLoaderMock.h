#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADERMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADERMOCK_CLASS_H

#include <gmock/gmock.h>

#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/Dxxwjz2Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"
#include "src/DarknetXX/weights/WeightsLoader.h"

namespace darknetxxi
{

/**
 * @brief The loader of the weights files, which tells the method a file
 * picks.
 */
class WeightsLoaderMock : public WeightsLoader
{
 public:
  MOCK_METHOD(bool, load, (const OrigWeights& weights), (override));
  MOCK_METHOD(bool, load, (const Dxxwjz1Weights& weights), (override));
  MOCK_METHOD(bool, load, (const Dxxwjz2Weights& weights), (override));
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WEIGHTSLOADERMOCK_CLASS_H
