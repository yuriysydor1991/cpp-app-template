#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "fontawesome-decls.h"
#include "src/fontawesome/FontAwesomeSvgsDirectory.h"

using namespace fontawesome;
using namespace testing;

class UTEST_FontAwesomeSvgsDirectory : public Test
{
 public:
  inline static const std::string missing{"/no/such/fontawesome/directory"};
  inline static const std::string fallback{"/the/fallback/directory"};

  const std::string existing{std::filesystem::temp_directory_path().string()};
};

TEST_F(UTEST_FontAwesomeSvgsDirectory, gives_the_first_existing_candidate)
{
  EXPECT_EQ(
      FontAwesomeSvgsDirectory::firstExisting({missing, existing}, fallback),
      existing);
}

TEST_F(UTEST_FontAwesomeSvgsDirectory, skips_the_empty_candidates)
{
  EXPECT_EQ(FontAwesomeSvgsDirectory::firstExisting({"", existing}, fallback),
            existing);
}

TEST_F(UTEST_FontAwesomeSvgsDirectory, gives_the_fallback_when_nothing_exists)
{
  EXPECT_EQ(FontAwesomeSvgsDirectory::firstExisting({"", missing}, fallback),
            fallback);
  EXPECT_EQ(FontAwesomeSvgsDirectory::firstExisting({}, fallback), fallback);
}

TEST_F(UTEST_FontAwesomeSvgsDirectory, finds_the_running_executable_directory)
{
  const auto binaryDir = FontAwesomeSvgsDirectory::executableDirectory();

  ASSERT_FALSE(binaryDir.empty());
  EXPECT_TRUE(std::filesystem::is_regular_file(
      std::filesystem::path{binaryDir} / "UTEST_FontAwesomeSvgsDirectory"));
}

TEST_F(UTEST_FontAwesomeSvgsDirectory,
       gives_the_configured_root_out_of_the_build)
{
  EXPECT_EQ(FontAwesomeSvgsDirectory::path(),
            fontawesome_decls::FONTAWESOME_SVGS_DIR);
}
