#include "src/plplot/PLplotDevicePicker.h"

#include <algorithm>
#include <string>
#include <vector>

namespace plploti
{

std::string PLplotDevicePicker::pick(
    const std::vector<std::string>& installed) const
{
  const auto found = std::find_if(
      preferred.begin(), preferred.end(), [&installed](const auto& device) {
        return std::find(installed.begin(), installed.end(), device) !=
               installed.end();
      });

  return found != preferred.end() ? *found : std::string{};
}

}  // namespace plploti
