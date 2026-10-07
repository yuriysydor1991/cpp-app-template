#include "src/DarknetXX/weights/NetworkWeights.h"

#include <string>
#include <utility>

namespace darknetxxi
{

NetworkWeights::NetworkWeights(std::string filePath)
    : mpath{std::move(filePath)}
{
}

const std::string& NetworkWeights::path() const { return mpath; }

}  // namespace darknetxxi
