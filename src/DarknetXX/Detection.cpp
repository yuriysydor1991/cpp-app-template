#include "src/DarknetXX/Detection.h"

#include <cmath>
#include <ostream>
#include <tuple>

namespace darknetxxi
{

bool Detection::operator==(const Detection& other) const
{
  return std::tie(name, probability, left, top, width, height) ==
         std::tie(other.name, other.probability, other.left, other.top,
                  other.width, other.height);
}

std::ostream& operator<<(std::ostream& stream, const Detection& detection)
{
  return stream << detection.name << ": "
                << std::lround(detection.probability * 100.0F) << "% ["
                << detection.left << ", " << detection.top << ", "
                << detection.width << " x " << detection.height << "]";
}

}  // namespace darknetxxi
