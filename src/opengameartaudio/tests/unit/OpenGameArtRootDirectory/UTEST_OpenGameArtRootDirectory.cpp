#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "opengameart-audio-decls.h"
#include "src/opengameartaudio/OpenGameArtRootDirectory.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtRootDirectory : public Test
{
 public:
  inline static const std::string missing{"/no/such/opengameart/directory"};
  inline static const std::string fallback{"/the/fallback/directory"};

  const std::string existing{std::filesystem::temp_directory_path().string()};
};

TEST_F(UTEST_OpenGameArtRootDirectory, gives_the_first_existing_candidate)
{
  EXPECT_EQ(
      OpenGameArtRootDirectory::firstExisting({missing, existing}, fallback),
      existing);
}

TEST_F(UTEST_OpenGameArtRootDirectory, skips_the_empty_candidates)
{
  EXPECT_EQ(OpenGameArtRootDirectory::firstExisting({"", existing}, fallback),
            existing);
}

TEST_F(UTEST_OpenGameArtRootDirectory, gives_the_fallback_when_nothing_exists)
{
  EXPECT_EQ(OpenGameArtRootDirectory::firstExisting({"", missing}, fallback),
            fallback);
  EXPECT_EQ(OpenGameArtRootDirectory::firstExisting({}, fallback), fallback);
}

TEST_F(UTEST_OpenGameArtRootDirectory, finds_the_running_executable_directory)
{
  const auto binaryDir = OpenGameArtRootDirectory::executableDirectory();

  ASSERT_FALSE(binaryDir.empty());
  EXPECT_TRUE(std::filesystem::is_regular_file(
      std::filesystem::path{binaryDir} / "UTEST_OpenGameArtRootDirectory"));
}

TEST_F(UTEST_OpenGameArtRootDirectory,
       gives_the_configured_root_out_of_the_build)
{
  EXPECT_EQ(OpenGameArtRootDirectory::path(),
            opengameart_audio_decls::OPENGAMEART_AUDIO_ROOT_DIR);
}
