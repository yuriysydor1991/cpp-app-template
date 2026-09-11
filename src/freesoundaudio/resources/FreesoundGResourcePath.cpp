#include "src/freesoundaudio/resources/FreesoundGResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/resources/FreesoundResourcePath.h"
#include "src/freesoundaudio/resources/IFreesoundResourcePath.h"

namespace freesoundaudio
{

FreesoundGResourcePath::FreesoundGResourcePath(std::string gprefix)
    : FreesoundResourcePath{std::move(gprefix)}
{
}

std::string FreesoundGResourcePath::of(const FreesoundSoundPtr& sound) const
{
  return prefixedAlias(sound);
}

std::string FreesoundGResourcePath::uriOf(const FreesoundSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IFreesoundResourcePathPtr FreesoundGResourcePath::create()
{
  return create(freesound_audio_decls::FREESOUND_AUDIO_GRESOURCE_PREFIX);
}

IFreesoundResourcePathPtr FreesoundGResourcePath::create(std::string gprefix)
{
  return std::make_shared<FreesoundGResourcePath>(std::move(gprefix));
}

}  // namespace freesoundaudio
