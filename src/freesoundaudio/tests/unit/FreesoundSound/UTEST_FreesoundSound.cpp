#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/categories/FreesoundCategory.h"

using namespace freesoundaudio;
using namespace testing;

class UTEST_FreesoundSound : public Test
{
 public:
  inline static const std::string expectedCategory{"interface-sounds"};
  inline static const std::string expectedPath{"Audio/click_001.ogg"};

  FreesoundSoundPtr create_sound(const std::string& gpath)
  {
    return FreesoundSound::create(FreesoundCategory::create(expectedCategory),
                                  gpath);
  }

  FreesoundSoundPtr sound{create_sound(expectedPath)};
};

TEST_F(UTEST_FreesoundSound, keeps_the_pack_and_the_path)
{
  EXPECT_EQ(sound->category()->name(), expectedCategory);
  EXPECT_EQ(sound->path(), expectedPath);
}

TEST_F(UTEST_FreesoundSound, derives_the_file_name_out_of_the_path)
{
  EXPECT_EQ(sound->fileName(), "click_001.ogg");
}

TEST_F(UTEST_FreesoundSound, derives_the_plain_name_out_of_the_path)
{
  EXPECT_EQ(sound->name(), "click_001");
}

TEST_F(UTEST_FreesoundSound, derives_the_extension_out_of_the_path)
{
  EXPECT_EQ(sound->extension(), "ogg");
}

TEST_F(UTEST_FreesoundSound, a_flat_path_stays_the_file_name)
{
  auto flat = create_sound("click_001.ogg");

  EXPECT_EQ(flat->fileName(), "click_001.ogg");
  EXPECT_EQ(flat->name(), "click_001");
  EXPECT_EQ(flat->extension(), "ogg");
}

TEST_F(UTEST_FreesoundSound, a_file_with_no_extension_reports_none)
{
  auto extensionless = create_sound("Audio/click_001");

  EXPECT_EQ(extensionless->name(), "click_001");
  EXPECT_TRUE(extensionless->extension().empty());
}

TEST_F(UTEST_FreesoundSound, the_alias_carries_the_pack_and_the_path)
{
  EXPECT_EQ(sound->alias(), expectedCategory + "/" + expectedPath);
}

TEST_F(UTEST_FreesoundSound, the_file_path_sits_under_the_configured_root)
{
  EXPECT_EQ(sound->filePath(), freesound_audio_decls::FREESOUND_AUDIO_ROOT_DIR +
                                   "/" + sound->alias());
}

TEST_F(UTEST_FreesoundSound, a_sound_with_no_pack_gives_no_alias)
{
  auto orphan = FreesoundSound::create(nullptr, expectedPath);

  EXPECT_TRUE(orphan->alias().empty());
  EXPECT_TRUE(orphan->filePath().empty());
}

TEST_F(UTEST_FreesoundSound, carries_the_recorded_license_and_source)
{
  EXPECT_EQ(sound->license(), "CC0-1.0");
  EXPECT_EQ(sound->sourceUrl(), "https://freesound.org/s/111111/");
}

TEST_F(UTEST_FreesoundSound, a_sound_the_manifest_never_named_reports_none)
{
  auto stranger = create_sound("Audio/no_such.ogg");

  EXPECT_TRUE(stranger->license().empty());
  EXPECT_TRUE(stranger->sourceUrl().empty());
}
