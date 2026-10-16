#include "src/Firebird/driver/FbDpbBuilder.h"

#include <string>
#include <vector>

namespace firebirdi::driver
{

FbDpbBuilder::FbDpbBuilder(char version) : dpb{version} {}

bool FbDpbBuilder::append(char tag, const std::string& value)
{
  if (value.empty()) {
    return true;
  }

  if (value.size() > max_value_length) {
    return false;
  }

  dpb.push_back(tag);
  dpb.push_back(static_cast<char>(static_cast<unsigned char>(value.size())));
  dpb.insert(dpb.end(), value.begin(), value.end());

  return true;
}

const std::vector<char>& FbDpbBuilder::data() const { return dpb; }

}  // namespace firebirdi::driver
