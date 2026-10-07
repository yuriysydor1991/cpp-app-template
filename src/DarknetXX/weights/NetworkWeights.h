#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_NETWORKWEIGHTS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_NETWORKWEIGHTS_CLASS_H

#include <memory>
#include <string>

#include "src/DarknetXX/weights/WeightsLoader.h"

namespace darknetxxi
{

/**
 * @brief A network weights file of a format the darknetxx reads. The
 * classes derived from this one stand for the formats.
 */
class NetworkWeights
{
 public:
  using NetworkWeightsPtr = std::shared_ptr<NetworkWeights>;

  virtual ~NetworkWeights() = default;
  explicit NetworkWeights(std::string filePath);

  const std::string& path() const;

  /**
   * @brief Loads the file by the loader method of it's format.
   *
   * @return Returns the loader result: true on success and false otherwise.
   */
  virtual bool load_into(WeightsLoader& loader) const = 0;

 private:
  std::string mpath;
};

using NetworkWeightsPtr = NetworkWeights::NetworkWeightsPtr;

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_NETWORKWEIGHTS_CLASS_H
