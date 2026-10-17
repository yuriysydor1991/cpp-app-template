#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "kenney-audio-decls.h"
#include "src/kenneyaudio/KenneyRootDirectory.h"

using namespace kenneyaudio;
using namespace testing;

class UTEST_KenneyRootDirectory : public Test
{
 public:
  inline static const std::string missing{"/no/such/kenney/directory"};
  inline static const std::string fallback{"/the/fallback/directory"};

  const std::string existing{std::filesystem::temp_directory_path().string()};
};

TEST_F(UTEST_KenneyRootDirectory, gives_the_first_existing_candidate)
{
  EXPECT_EQ(KenneyRootDirectory::firstExisting({missing, existing}, fallback),
            existing);
}

TEST_F(UTEST_KenneyRootDirectory, skips_the_empty_candidates)
{
  EXPECT_EQ(KenneyRootDirectory::firstExisting({"", existing}, fallback),
            existing);
}

TEST_F(UTEST_KenneyRootDirectory, gives_the_fallback_when_nothing_exists)
{
  EXPECT_EQ(KenneyRootDirectory::firstExisting({"", missing}, fallback),
            fallback);
  EXPECT_EQ(KenneyRootDirectory::firstExisting({}, fallback), fallback);
}

TEST_F(UTEST_KenneyRootDirectory, finds_the_running_executable_directory)
{
  const auto binaryDir = KenneyRootDirectory::executableDirectory();

  ASSERT_FALSE(binaryDir.empty());
  EXPECT_TRUE(std::filesystem::is_regular_file(
      std::filesystem::path{binaryDir} / "UTEST_KenneyRootDirectory"));
}

TEST_F(UTEST_KenneyRootDirectory, gives_the_configured_root_out_of_the_build)
{
  EXPECT_EQ(KenneyRootDirectory::path(),
            kenney_audio_decls::KENNEY_AUDIO_ROOT_DIR);
}
