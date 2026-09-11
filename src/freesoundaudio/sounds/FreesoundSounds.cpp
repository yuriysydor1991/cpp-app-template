#include "src/freesoundaudio/sounds/FreesoundSounds.h"

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/categories/FreesoundCategories.h"
#include "src/freesoundaudio/categories/IFreesoundCategories.h"
#include "src/freesoundaudio/sounds/FreesoundGeneratedSounds.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"
#include "src/log/log.h"

namespace freesoundaudio
{

FreesoundSounds::FreesoundSounds(IFreesoundCategoriesPtr gpacks)
{
  assert(gpacks != nullptr);

  if (gpacks == nullptr) {
    LOGE("No categories to gather the sounds of");
    return;
  }

  for (const auto& category : gpacks->all()) {
    // The name is materialized because IFreesoundCategory::name gives it by
    // value and the index answers with a reference into it's own storage.
    const auto categoryName = category->name();

    for (const auto& soundPath :
         FreesoundGeneratedSounds::names(categoryName)) {
      msounds.push_back(FreesoundSound::create(category, soundPath));
    }
  }
}

const FreesoundSounds::SoundsList& FreesoundSounds::all() const
{
  return msounds;
}

FreesoundSounds::SoundsList FreesoundSounds::ofCategory(
    const std::string& categoryName) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->category()->name() == categoryName) {
      found.push_back(sound);
    }
  }

  return found;
}

FreesoundSoundPtr FreesoundSounds::find(const std::string& categoryName,
                                        const std::string& soundPath) const
{
  for (const auto& sound : msounds) {
    if (sound->category()->name() == categoryName &&
        sound->path() == soundPath) {
      return sound;
    }
  }

  return {};
}

FreesoundSounds::SoundsList FreesoundSounds::search(
    const std::string& namePart) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->name().find(namePart) != std::string::npos) {
      found.push_back(sound);
    }
  }

  return found;
}

std::size_t FreesoundSounds::count() const { return msounds.size(); }

IFreesoundSoundsPtr FreesoundSounds::create()
{
  return create(FreesoundCategories::create());
}

IFreesoundSoundsPtr FreesoundSounds::create(IFreesoundCategoriesPtr gpacks)
{
  return std::make_shared<FreesoundSounds>(std::move(gpacks));
}

}  // namespace freesoundaudio
