#include "src/opengameartaudio/resources/OpenGameArtGResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "opengameart-audio-decls.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/resources/IOpenGameArtResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtResourcePath.h"

namespace opengameartaudio
{

OpenGameArtGResourcePath::OpenGameArtGResourcePath(std::string gprefix)
    : OpenGameArtResourcePath{std::move(gprefix)}
{
}

std::string OpenGameArtGResourcePath::of(const OpenGameArtSoundPtr& sound) const
{
  return prefixedAlias(sound);
}

std::string OpenGameArtGResourcePath::uriOf(
    const OpenGameArtSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IOpenGameArtResourcePathPtr OpenGameArtGResourcePath::create()
{
  return create(opengameart_audio_decls::OPENGAMEART_AUDIO_GRESOURCE_PREFIX);
}

IOpenGameArtResourcePathPtr OpenGameArtGResourcePath::create(
    std::string gprefix)
{
  return std::make_shared<OpenGameArtGResourcePath>(std::move(gprefix));
}

}  // namespace opengameartaudio
