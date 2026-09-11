#include "src/kenneyaudio/resources/KenneyResourcePath.h"

#include <cassert>
#include <string>
#include <utility>

#include "src/kenneyaudio/KenneySound.h"
#include "src/log/log.h"

namespace kenneyaudio
{

KenneyResourcePath::KenneyResourcePath(std::string gprefix)
    : mprefix{normalized(std::move(gprefix))}
{
}

std::string KenneyResourcePath::normalized(std::string gprefix)
{
  while (!gprefix.empty() && gprefix.back() == '/') {
    gprefix.pop_back();
  }

  if (gprefix.empty() || gprefix.front() != '/') {
    gprefix.insert(gprefix.cbegin(), '/');
  }

  return gprefix;
}

const std::string& KenneyResourcePath::prefix() const { return mprefix; }

std::string KenneyResourcePath::prefixedAlias(const KenneySoundPtr& sound) const
{
  assert(sound != nullptr);

  if (sound == nullptr) {
    LOGE("No sound to give the resource path of");
    return {};
  }

  return mprefix + "/" + sound->alias();
}

}  // namespace kenneyaudio
