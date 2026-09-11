#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/resources/IKenneyResourcePath.h"
#include "src/kenneyaudio/resources/KenneyResourcePath.h"

namespace kenneyaudio
{

KenneyQtResourcePath::KenneyQtResourcePath(std::string gprefix)
    : KenneyResourcePath{std::move(gprefix)}
{
}

std::string KenneyQtResourcePath::of(const KenneySoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_MARK + alias;
}

std::string KenneyQtResourcePath::uriOf(const KenneySoundPtr& sound) const
{
  const auto alias = prefixedAlias(sound);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IKenneyResourcePathPtr KenneyQtResourcePath::create()
{
  return create(kenney_audio_decls::KENNEY_AUDIO_QT_RESOURCE_PREFIX);
}

IKenneyResourcePathPtr KenneyQtResourcePath::create(std::string gprefix)
{
  return std::make_shared<KenneyQtResourcePath>(std::move(gprefix));
}

}  // namespace kenneyaudio
