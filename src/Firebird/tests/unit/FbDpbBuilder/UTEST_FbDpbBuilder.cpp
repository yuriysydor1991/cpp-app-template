#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "src/Firebird/driver/FbDpbBuilder.h"

using namespace firebirdi::driver;
using namespace testing;

class UTEST_FbDpbBuilder : public Test
{
 public:
  UTEST_FbDpbBuilder() : dpb{std::make_shared<FbDpbBuilder>(version)} {}

  static constexpr char version{1};
  static constexpr char tag{28};

  std::shared_ptr<FbDpbBuilder> dpb;
};

TEST_F(UTEST_FbDpbBuilder, starts_with_the_version)
{
  EXPECT_THAT(dpb->data(), ElementsAre(version));
}

TEST_F(UTEST_FbDpbBuilder, appends_the_tag_the_length_and_the_value)
{
  EXPECT_TRUE(dpb->append(tag, "SYSDBA"));

  EXPECT_THAT(dpb->data(),
              ElementsAre(version, tag, 6, 'S', 'Y', 'S', 'D', 'B', 'A'));
}

TEST_F(UTEST_FbDpbBuilder, skips_the_empty_value)
{
  EXPECT_TRUE(dpb->append(tag, {}));

  EXPECT_THAT(dpb->data(), ElementsAre(version));
}

TEST_F(UTEST_FbDpbBuilder, accepts_the_longest_single_byte_length)
{
  const std::string value(FbDpbBuilder::max_value_length, 'x');

  EXPECT_TRUE(dpb->append(tag, value));

  ASSERT_EQ(dpb->data().size(), value.size() + 3U);
  EXPECT_EQ(static_cast<unsigned char>(dpb->data()[2]), 255U);
}

TEST_F(UTEST_FbDpbBuilder, refuses_a_too_long_value)
{
  const std::string value(FbDpbBuilder::max_value_length + 1U, 'x');

  EXPECT_FALSE(dpb->append(tag, value));

  EXPECT_THAT(dpb->data(), ElementsAre(version));
}
