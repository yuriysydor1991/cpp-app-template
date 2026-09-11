#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/resources/FreesoundResourcePath.h"
#include "src/freesoundaudio/resources/IFreesoundResourcePath.h"

namespace freesoundaudio
{

FreesoundQtResourcePath::FreesoundQtResourcePath(std::string gprefix)
    : FreesoundResourcePath{std::move(gprefix)}
{
}

std::string FreesoundQtResourcePath::of(const FreesoundSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_MARK + alias;
}

std::string FreesoundQtResourcePath::uriOf(const FreesoundSoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IFreesoundResourcePathPtr FreesoundQtResourcePath::create()
{
  return create(freesound_audio_decls::FREESOUND_AUDIO_QT_RESOURCE_PREFIX);
}

IFreesoundResourcePathPtr FreesoundQtResourcePath::create(std::string gprefix)
{
  return std::make_shared<FreesoundQtResourcePath>(std::move(gprefix));
}

}  // namespace freesoundaudio
