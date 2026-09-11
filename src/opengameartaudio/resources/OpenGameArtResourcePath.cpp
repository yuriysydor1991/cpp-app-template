#include "src/opengameartaudio/resources/OpenGameArtResourcePath.h"

#include <cassert>
#include <string>
#include <utility>

#include "src/log/log.h"
#include "src/opengameartaudio/OpenGameArtSound.h"

namespace opengameartaudio
{

OpenGameArtResourcePath::OpenGameArtResourcePath(std::string gprefix)
    : mprefix{normalized(std::move(gprefix))}
{
}

std::string OpenGameArtResourcePath::normalized(std::string gprefix)
{
  while (!gprefix.empty() && gprefix.back() == '/') {
    gprefix.pop_back();
  }

  if (gprefix.empty() || gprefix.front() != '/') {
    gprefix.insert(gprefix.cbegin(), '/');
  }

  return gprefix;
}

const std::string& OpenGameArtResourcePath::prefix() const { return mprefix; }

std::string OpenGameArtResourcePath::prefixedAlias(
    const OpenGameArtSoundPtr& sound) const
{
  assert(sound != nullptr);

  if (sound == nullptr) {
    LOGE("No sound to give the resource path of");
    return {};
  }

  return mprefix + "/" + sound->alias();
}

}  // namespace opengameartaudio
