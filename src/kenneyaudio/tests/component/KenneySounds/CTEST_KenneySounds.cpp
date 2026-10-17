#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <set>
#include <string>

#include "src/kenneyaudio/KenneyRootDirectory.h"
#include "src/kenneyaudio/resources/KenneyGResourcePath.h"
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"
#include "src/kenneyaudio/sounds/KenneySounds.h"

using namespace kenneyaudio;
using namespace testing;

// Answers for the packs the project has really been configured with, so it
// reads the very index the kenney audio enabler has generated instead of a
// stand-in one.
class CTEST_KenneySounds : public Test
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
                   << " manifest: the KENNEY_AUDIO_GENERATE_FULL_MANIFESTS"
                      " option is off";
    }

    EXPECT_EQ(aliasesOf(manifest), gatheredAliases());
  }

  IKenneySoundsPtr sounds{KenneySounds::create()};
};

TEST_F(CTEST_KenneySounds, the_configured_packs_carry_sounds)
{
  EXPECT_GT(sounds->count(), 0u);
  EXPECT_EQ(sounds->all().size(), sounds->count());
}

TEST_F(CTEST_KenneySounds, every_sound_file_is_really_there)
{
  for (const auto& sound : sounds->all()) {
    std::ifstream soundFile{sound->filePath(), std::ios::binary};

    EXPECT_TRUE(soundFile.good())
        << "No " << sound->filePath() << " sound file of the " << sound->alias()
        << " alias";
  }
}

TEST_F(CTEST_KenneySounds, every_sound_is_reachable_by_it_s_pack_and_path)
{
  for (const auto& sound : sounds->all()) {
    EXPECT_EQ(sounds->find(sound->pack()->name(), sound->path()), sound);
  }
}

TEST_F(CTEST_KenneySounds, every_sound_carries_an_own_alias)
{
  for (const auto& sound : sounds->all()) {
    EXPECT_EQ(sounds->search(sound->name()).empty(), false);
    EXPECT_FALSE(sound->alias().empty());
    EXPECT_FALSE(sound->extension().empty());
  }

  EXPECT_EQ(gatheredAliases().size(), sounds->count());
}

TEST_F(CTEST_KenneySounds, the_generated_qt_manifest_lists_every_sound)
{
  expectEverySoundIn(CTEST_KenneySounds_QRC);
}

TEST_F(CTEST_KenneySounds, the_generated_gresource_manifest_lists_every_sound)
{
  expectEverySoundIn(CTEST_KenneySounds_GRESOURCE_XML);
}

TEST_F(CTEST_KenneySounds, every_pack_carries_it_s_license_file)
{
  for (const auto& sound : sounds->all()) {
    EXPECT_TRUE(std::filesystem::is_regular_file(KenneyRootDirectory::path() +
                                                 "/" + sound->pack()->name() +
                                                 "/License.txt"))
        << "No license file of the " << sound->pack()->name() << " pack";
  }
}

TEST_F(CTEST_KenneySounds, every_sound_resolves_through_both_resource_systems)
{
  auto qt = KenneyQtResourcePath::create();
  auto gresource = KenneyGResourcePath::create();

  for (const auto& sound : sounds->all()) {
    EXPECT_THAT(qt->of(sound), EndsWith(sound->alias()));
    EXPECT_THAT(qt->uriOf(sound), StartsWith("qrc:"));
    EXPECT_THAT(gresource->of(sound), EndsWith(sound->alias()));
    EXPECT_THAT(gresource->uriOf(sound), StartsWith("resource://"));
  }
}
