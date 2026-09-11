#include "src/freesoundaudio/resources/FreesoundResourcePath.h"

#include <cassert>
#include <string>
#include <utility>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/log/log.h"

namespace freesoundaudio
{

FreesoundResourcePath::FreesoundResourcePath(std::string gprefix)
    : mprefix{normalized(std::move(gprefix))}
{
}

std::string FreesoundResourcePath::normalized(std::string gprefix)
{
  while (!gprefix.empty() && gprefix.back() == '/') {
    gprefix.pop_back();
  }

  if (gprefix.empty() || gprefix.front() != '/') {
    gprefix.insert(gprefix.cbegin(), '/');
  }

  return gprefix;
}

const std::string& FreesoundResourcePath::prefix() const { return mprefix; }

std::string FreesoundResourcePath::prefixedAlias(
    const FreesoundSoundPtr& sound) const
{
  assert(sound != nullptr);

  if (sound == nullptr) {
    LOGE("No sound to give the resource path of");
    return {};
  }

  return mprefix + "/" + sound->alias();
}

}  // namespace freesoundaudio
