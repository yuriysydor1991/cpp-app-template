#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DETECTION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DETECTION_CLASS_H

#include <ostream>
#include <string>

namespace darknetxxi
{

/**
 * @brief An object the network detected in an image: the name of it's class,
 * the probability of the class and the bounding box in the image pixels.
 */
class Detection
{
 public:
  bool operator==(const Detection& other) const;

  std::string name;
  float probability{0.0F};
  int left{0};
  int top{0};
  int width{0};
  int height{0};
};

/// @brief Prints the detection the "dog: 98% [left, top, width x height]" way.
std::ostream& operator<<(std::ostream& stream, const Detection& detection);

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DETECTION_CLASS_H
