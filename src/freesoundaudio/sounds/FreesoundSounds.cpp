#include "src/freesoundaudio/sounds/FreesoundSounds.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
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

FreesoundSounds::FreesoundSounds(IFreesoundCategoriesPtr gcategories)
{
  assert(gcategories != nullptr);

  if (gcategories == nullptr) {
    LOGE("No categories to gather the sounds of");
    return;
  }

  for (const auto& category : gcategories->all()) {
    // The name is materialized because IFreesoundCategory::name gives it by
    // value and the index answers with a reference into it's own storage.
    const auto categoryName = category->name();

    const auto& soundPaths = FreesoundGeneratedSounds::names(categoryName);

    std::transform(soundPaths.cbegin(), soundPaths.cend(),
                   std::back_inserter(msounds),
                   [&category](const auto& soundPath) {
                     return FreesoundSound::create(category, soundPath);
                   });
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

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&categoryName](const auto& sound) {
                 return sound->category()->name() == categoryName;
               });

  return found;
}

FreesoundSoundPtr FreesoundSounds::find(const std::string& categoryName,
                                        const std::string& soundPath) const
{
  const auto found =
      std::find_if(msounds.cbegin(), msounds.cend(),
                   [&categoryName, &soundPath](const auto& sound) {
                     return sound->category()->name() == categoryName &&
                            sound->path() == soundPath;
                   });

  return found == msounds.cend() ? FreesoundSoundPtr{} : *found;
}

FreesoundSounds::SoundsList FreesoundSounds::search(
    const std::string& namePart) const
{
  SoundsList found;

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&namePart](const auto& sound) {
                 return sound->name().find(namePart) != std::string::npos;
               });

  return found;
}

std::size_t FreesoundSounds::count() const { return msounds.size(); }

IFreesoundSoundsPtr FreesoundSounds::create()
{
  return create(FreesoundCategories::create());
}

IFreesoundSoundsPtr FreesoundSounds::create(IFreesoundCategoriesPtr gcategories)
{
  return std::make_shared<FreesoundSounds>(std::move(gcategories));
}

}  // namespace freesoundaudio
