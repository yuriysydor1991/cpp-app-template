#include "src/opengameartaudio/OpenGameArtSound.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>

#include "opengameart-audio-decls.h"
#include "src/log/log.h"
#include "src/opengameartaudio/packs/IOpenGameArtPack.h"

namespace opengameartaudio
{

OpenGameArtSound::OpenGameArtSound(IOpenGameArtPackPtr gpack, std::string gpath)
    : mpack{std::move(gpack)}, mpath{std::move(gpath)}
{
  assert(mpack != nullptr);
}

const IOpenGameArtPackPtr& OpenGameArtSound::pack() const { return mpack; }

const std::string& OpenGameArtSound::path() const { return mpath; }

std::string OpenGameArtSound::fileName() const
{
  const auto separator = mpath.find_last_of('/');

  if (separator == std::string::npos) {
    return mpath;
  }

  return mpath.substr(separator + 1);
}

std::string OpenGameArtSound::name() const
{
  auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return file;
  }

  return file.substr(0, dot);
}

std::string OpenGameArtSound::extension() const
{
  const auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return {};
  }

  return file.substr(dot + 1);
}

std::string OpenGameArtSound::alias() const
{
  if (mpack == nullptr) {
    LOGE("No pack to give the sound alias of");
    return {};
  }

  return mpack->name() + "/" + mpath;
}

std::string OpenGameArtSound::filePath() const
{
  const auto soundAlias = alias();

  if (soundAlias.empty()) {
    return {};
  }

  return opengameart_audio_decls::OPENGAMEART_AUDIO_ROOT_DIR + "/" + soundAlias;
}

OpenGameArtSoundPtr OpenGameArtSound::create(IOpenGameArtPackPtr gpack,
                                             std::string gpath)
{
  return std::make_shared<OpenGameArtSound>(std::move(gpack), std::move(gpath));
}

}  // namespace opengameartaudio
