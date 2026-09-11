#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "opengameart-audio-decls.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/resources/IOpenGameArtResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtResourcePath.h"

namespace opengameartaudio
{

OpenGameArtQtResourcePath::OpenGameArtQtResourcePath(std::string gprefix)
    : OpenGameArtResourcePath{std::move(gprefix)}
{
}

std::string OpenGameArtQtResourcePath::of(
    const OpenGameArtSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_MARK + alias;
}

std::string OpenGameArtQtResourcePath::uriOf(
    const OpenGameArtSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IOpenGameArtResourcePathPtr OpenGameArtQtResourcePath::create()
{
  return create(opengameart_audio_decls::OPENGAMEART_AUDIO_QT_RESOURCE_PREFIX);
}

IOpenGameArtResourcePathPtr OpenGameArtQtResourcePath::create(
    std::string gprefix)
{
  return std::make_shared<OpenGameArtQtResourcePath>(std::move(gprefix));
}

}  // namespace opengameartaudio
