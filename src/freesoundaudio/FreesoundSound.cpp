#include "src/freesoundaudio/FreesoundSound.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/categories/IFreesoundCategory.h"
#include "src/freesoundaudio/sounds/FreesoundGeneratedSounds.h"
#include "src/log/log.h"

namespace freesoundaudio
{

FreesoundSound::FreesoundSound(IFreesoundCategoryPtr gcategory,
                               std::string gpath)
    : mcategory{std::move(gcategory)}, mpath{std::move(gpath)}
{
  assert(mcategory != nullptr);
}

const IFreesoundCategoryPtr& FreesoundSound::category() const
{
  return mcategory;
}

const std::string& FreesoundSound::path() const { return mpath; }

std::string FreesoundSound::fileName() const
{
  const auto separator = mpath.find_last_of('/');

  if (separator == std::string::npos) {
    return mpath;
  }

  return mpath.substr(separator + 1);
}

std::string FreesoundSound::name() const
{
  auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return file;
  }

  return file.substr(0, dot);
}

std::string FreesoundSound::extension() const
{
  const auto file = fileName();

  const auto dot = file.find_last_of('.');

  if (dot == std::string::npos) {
    return {};
  }

  return file.substr(dot + 1);
}

std::string FreesoundSound::alias() const
{
  if (mcategory == nullptr) {
    LOGE("No category to give the sound alias of");
    return {};
  }

  return mcategory->name() + "/" + mpath;
}

std::string FreesoundSound::filePath() const
{
  const auto soundAlias = alias();

  if (soundAlias.empty()) {
    return {};
  }

  return freesound_audio_decls::FREESOUND_AUDIO_ROOT_DIR + "/" + soundAlias;
}

std::string FreesoundSound::license() const
{
  return FreesoundGeneratedSounds::license(alias());
}

std::string FreesoundSound::sourceUrl() const
{
  return FreesoundGeneratedSounds::sourceUrl(alias());
}

FreesoundSoundPtr FreesoundSound::create(IFreesoundCategoryPtr gcategory,
                                         std::string gpath)
{
  return std::make_shared<FreesoundSound>(std::move(gcategory),
                                          std::move(gpath));
}

}  // namespace freesoundaudio
