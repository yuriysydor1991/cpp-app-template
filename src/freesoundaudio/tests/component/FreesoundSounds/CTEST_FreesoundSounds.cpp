#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "src/freesoundaudio/resources/FreesoundGResourcePath.h"
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"
#include "src/freesoundaudio/sounds/FreesoundSounds.h"

using namespace freesoundaudio;
using namespace testing;

// Answers for the categories the project has really been configured with, so it
// reads the very index the freesound audio enabler has generated instead of a
// stand-in one.
class CTEST_FreesoundSounds : public Test
{
 public:
  /// @brief Gathers the aliases the given resource manifest keys it's files
  /// by, which is the single naming the manifest and the code agree upon.
  static std::set<std::string> aliasesOf(const std::string& manifestPath)
  {
    static const std::string aliasMark = "alias=\"";

    std::set<std::string> aliases;
    std::ifstream manifest{manifestPath};
    std::string line;

    while (std::getline(manifest, line)) {
      const auto aliasStart = line.find(aliasMark);

      if (aliasStart == std::string::npos) {
        continue;
      }

      const auto valueStart = aliasStart + aliasMark.size();
      const auto valueEnd = line.find('"', valueStart);

      if (valueEnd != std::string::npos) {
        aliases.insert(line.substr(valueStart, valueEnd - valueStart));
      }
    }

    return aliases;
  }

  std::set<std::string> gatheredAliases() const
  {
    std::set<std::string> aliases;

    for (const auto& sound : sounds->all()) {
      aliases.insert(sound->alias());
    }

    return aliases;
  }

  void expectEverySoundIn(const std::string& manifest) const
  {
    if (!std::filesystem::is_regular_file(manifest)) {
      GTEST_SKIP() << "no " << manifest
                   << " manifest: the FREESOUND_AUDIO_GENERATE_FULL_MANIFESTS"
                      " option is off";
    }

    EXPECT_EQ(aliasesOf(manifest), gatheredAliases());
  }

  IFreesoundSoundsPtr sounds{FreesoundSounds::create()};
};

TEST_F(CTEST_FreesoundSounds, the_configured_packs_carry_sounds)
{
  EXPECT_GT(sounds->count(), 0u);
  EXPECT_EQ(sounds->all().size(), sounds->count());
}

TEST_F(CTEST_FreesoundSounds, every_sound_file_is_really_there)
{
  for (const auto& sound : sounds->all()) {
    std::ifstream soundFile{sound->filePath(), std::ios::binary};

    EXPECT_TRUE(soundFile.good())
        << "No " << sound->filePath() << " sound file of the " << sound->alias()
        << " alias";
  }
}

TEST_F(CTEST_FreesoundSounds, every_sound_is_reachable_by_it_s_pack_and_path)
{
  for (const auto& sound : sounds->all()) {
    EXPECT_EQ(sounds->find(sound->category()->name(), sound->path()), sound);
  }
}

TEST_F(CTEST_FreesoundSounds, every_sound_carries_an_own_alias)
{
  for (const auto& sound : sounds->all()) {
    EXPECT_EQ(sounds->search(sound->name()).empty(), false);
    EXPECT_FALSE(sound->alias().empty());
    EXPECT_FALSE(sound->extension().empty());
  }

  EXPECT_EQ(gatheredAliases().size(), sounds->count());
}

TEST_F(CTEST_FreesoundSounds, the_generated_qt_manifest_lists_every_sound)
{
  expectEverySoundIn(CTEST_FreesoundSounds_QRC);
}

TEST_F(CTEST_FreesoundSounds,
       the_generated_gresource_manifest_lists_every_sound)
{
  expectEverySoundIn(CTEST_FreesoundSounds_GRESOURCE_XML);
}

TEST_F(CTEST_FreesoundSounds, every_sound_carries_the_manifest_license)
{
  // <category>/<file>|<download URL>|<license>|<file SHA-256> lines, the '#'
  // starting a comment
  std::ifstream manifest{CTEST_FreesoundSounds_MANIFEST};
  std::map<std::string, std::pair<std::string, std::string>> recorded;
  std::string line;

  ASSERT_TRUE(manifest.is_open());

  while (std::getline(manifest, line)) {
    const auto aliasEnd = line.find('|');
    const auto urlEnd = line.find('|', aliasEnd + 1);

    if (line.empty() || line.front() == '#' || urlEnd == std::string::npos) {
      continue;
    }

    recorded[line.substr(0, aliasEnd)] = {
        line.substr(aliasEnd + 1, urlEnd - aliasEnd - 1),
        line.substr(urlEnd + 1, line.find('|', urlEnd + 1) - urlEnd - 1)};
  }

  for (const auto& sound : sounds->all()) {
    EXPECT_FALSE(sound->license().empty()) << sound->alias();
    EXPECT_EQ(sound->license(), recorded[sound->alias()].second)
        << sound->alias();
    EXPECT_EQ(sound->sourceUrl(), recorded[sound->alias()].first)
        << sound->alias();
  }
}
