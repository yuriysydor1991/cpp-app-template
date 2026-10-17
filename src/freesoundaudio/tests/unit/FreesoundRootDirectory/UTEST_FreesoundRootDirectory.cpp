#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "freesound-audio-decls.h"
#include "src/freesoundaudio/FreesoundRootDirectory.h"

using namespace freesoundaudio;
using namespace testing;

class UTEST_FreesoundRootDirectory : public Test
{
 public:
  inline static const std::string missing{"/no/such/freesound/directory"};
  inline static const std::string fallback{"/the/fallback/directory"};

  const std::string existing{std::filesystem::temp_directory_path().string()};
};

TEST_F(UTEST_FreesoundRootDirectory, gives_the_first_existing_candidate)
{
  EXPECT_EQ(
      FreesoundRootDirectory::firstExisting({missing, existing}, fallback),
      existing);
}

TEST_F(UTEST_FreesoundRootDirectory, skips_the_empty_candidates)
{
  EXPECT_EQ(FreesoundRootDirectory::firstExisting({"", existing}, fallback),
            existing);
}

TEST_F(UTEST_FreesoundRootDirectory, gives_the_fallback_when_nothing_exists)
{
  EXPECT_EQ(FreesoundRootDirectory::firstExisting({"", missing}, fallback),
            fallback);
  EXPECT_EQ(FreesoundRootDirectory::firstExisting({}, fallback), fallback);
}

TEST_F(UTEST_FreesoundRootDirectory, finds_the_running_executable_directory)
{
  const auto binaryDir = FreesoundRootDirectory::executableDirectory();

  ASSERT_FALSE(binaryDir.empty());
  EXPECT_TRUE(std::filesystem::is_regular_file(
      std::filesystem::path{binaryDir} / "UTEST_FreesoundRootDirectory"));
}

TEST_F(UTEST_FreesoundRootDirectory, gives_the_configured_root_out_of_the_build)
{
  EXPECT_EQ(FreesoundRootDirectory::path(),
            freesound_audio_decls::FREESOUND_AUDIO_ROOT_DIR);
}
