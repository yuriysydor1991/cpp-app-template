#include "src/kenneyaudio/resources/KenneyGResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/resources/IKenneyResourcePath.h"
#include "src/kenneyaudio/resources/KenneyResourcePath.h"

namespace kenneyaudio
{

KenneyGResourcePath::KenneyGResourcePath(std::string gprefix)
    : KenneyResourcePath{std::move(gprefix)}
{
}

std::string KenneyGResourcePath::of(const KenneySoundPtr& sound) const
{
  return prefixedAlias(sound);
}

std::string KenneyGResourcePath::uriOf(const KenneySoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IKenneyResourcePathPtr KenneyGResourcePath::create()
{
  return create(kenney_audio_decls::KENNEY_AUDIO_GRESOURCE_PREFIX);
}

IKenneyResourcePathPtr KenneyGResourcePath::create(std::string gprefix)
{
  return std::make_shared<KenneyGResourcePath>(std::move(gprefix));
}

}  // namespace kenneyaudio
