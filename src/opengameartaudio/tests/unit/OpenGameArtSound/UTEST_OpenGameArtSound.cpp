#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "opengameart-audio-decls.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/packs/OpenGameArtPack.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtSound : public Test
{
 public:
  inline static const std::string expectedPack{"interface-sounds"};
  inline static const std::string expectedPath{"Audio/click_001.ogg"};
  inline static const std::string expectedLicense{"CC0-1.0"};

  OpenGameArtSoundPtr create_sound(const std::string& gpath)
  {
    return OpenGameArtSound::create(
        OpenGameArtPack::create(expectedPack, expectedLicense), gpath);
  }

  OpenGameArtSoundPtr sound{create_sound(expectedPath)};
};

TEST_F(UTEST_OpenGameArtSound, keeps_the_pack_and_the_path)
{
  EXPECT_EQ(sound->pack()->name(), expectedPack);
  EXPECT_EQ(sound->path(), expectedPath);
}

TEST_F(UTEST_OpenGameArtSound, derives_the_file_name_out_of_the_path)
{
  EXPECT_EQ(sound->fileName(), "click_001.ogg");
}

TEST_F(UTEST_OpenGameArtSound, derives_the_plain_name_out_of_the_path)
{
  EXPECT_EQ(sound->name(), "click_001");
}

TEST_F(UTEST_OpenGameArtSound, derives_the_extension_out_of_the_path)
{
  EXPECT_EQ(sound->extension(), "ogg");
}

TEST_F(UTEST_OpenGameArtSound, a_flat_path_stays_the_file_name)
{
  auto flat = create_sound("click_001.ogg");

  EXPECT_EQ(flat->fileName(), "click_001.ogg");
  EXPECT_EQ(flat->name(), "click_001");
  EXPECT_EQ(flat->extension(), "ogg");
}

TEST_F(UTEST_OpenGameArtSound, a_file_with_no_extension_reports_none)
{
  auto extensionless = create_sound("Audio/click_001");

  EXPECT_EQ(extensionless->name(), "click_001");
  EXPECT_TRUE(extensionless->extension().empty());
}

TEST_F(UTEST_OpenGameArtSound, the_alias_carries_the_pack_and_the_path)
{
  EXPECT_EQ(sound->alias(), expectedPack + "/" + expectedPath);
}

TEST_F(UTEST_OpenGameArtSound, the_file_path_sits_under_the_configured_root)
{
  EXPECT_EQ(sound->filePath(),
            opengameart_audio_decls::OPENGAMEART_AUDIO_ROOT_DIR + "/" +
                sound->alias());
}

TEST_F(UTEST_OpenGameArtSound, a_sound_with_no_pack_gives_no_alias)
{
  auto orphan = OpenGameArtSound::create(nullptr, expectedPath);

  EXPECT_TRUE(orphan->alias().empty());
  EXPECT_TRUE(orphan->filePath().empty());
}
