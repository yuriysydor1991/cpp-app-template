#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

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
}

TEST_F(CTEST_FreesoundSounds,
       every_sound_resolves_through_both_resource_systems)
{
  auto qt = FreesoundQtResourcePath::create();
  auto gresource = FreesoundGResourcePath::create();

  for (const auto& sound : sounds->all()) {
    EXPECT_THAT(qt->of(sound), EndsWith(sound->alias()));
    EXPECT_THAT(qt->uriOf(sound), StartsWith("qrc:"));
    EXPECT_THAT(gresource->of(sound), EndsWith(sound->alias()));
    EXPECT_THAT(gresource->uriOf(sound), StartsWith("resource://"));
  }
}
