#include "src/kenneyaudio/KenneySound.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/packs/IKenneyPack.h"
#include "src/log/log.h"

namespace kenneyaudio
{

KenneySound::KenneySound(IKenneyPackPtr gpack, std::string gpath)
    : mpack{std::move(gpack)}, mpath{std::move(gpath)}
{
  assert(mpack != nullptr);
}

const IKenneyPackPtr& KenneySound::pack() const { return mpack; }

const std::string& KenneySound::path() const { return mpath; }

std::string KenneySound::fileName() const
{
  const auto separator = mpath.find_last_of('/');

  if (separator == std::string::npos) {
    return mpath;
  }

  return mpath.substr(separator + 1);
}

std::string KenneySound::name() const
{
  auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return file;
  }

  return file.substr(0, dot);
}

std::string KenneySound::extension() const
{
  const auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return {};
  }

  return file.substr(dot + 1);
}

std::string KenneySound::alias() const
{
  if (mpack == nullptr) {
    LOGE("No pack to give the sound alias of");
    return {};
  }

  return mpack->name() + "/" + mpath;
}

std::string KenneySound::filePath() const
{
  const auto soundAlias = alias();

  if (soundAlias.empty()) {
    return {};
  }

  return kenney_audio_decls::KENNEY_AUDIO_ROOT_DIR + "/" + soundAlias;
}

KenneySoundPtr KenneySound::create(IKenneyPackPtr gpack, std::string gpath)
{
  return std::make_shared<KenneySound>(std::move(gpack), std::move(gpath));
}

}  // namespace kenneyaudio
