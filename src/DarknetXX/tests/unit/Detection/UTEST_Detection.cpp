#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "src/DarknetXX/Detection.h"

using namespace darknetxxi;
using namespace testing;

class UTEST_Detection : public Test
{
 public:
  static std::string printed(const Detection& detection)
  {
    std::ostringstream stream;

    stream << detection;

    return stream.str();
  }

  Detection dog{"dog", 0.84F, 137, 205, 181, 332};
};

TEST_F(UTEST_Detection, prints_the_name_the_percents_and_the_box)
{
  EXPECT_EQ(printed(dog), "dog: 84% [137, 205, 181 x 332]");
}

TEST_F(UTEST_Detection, prints_the_rounded_percents)
{
  dog.probability = 0.456F;

  EXPECT_EQ(printed(dog), "dog: 46% [137, 205, 181 x 332]");
}

TEST_F(UTEST_Detection, the_same_detections_are_equal)
{
  EXPECT_EQ(dog, (Detection{"dog", 0.84F, 137, 205, 181, 332}));
}

TEST_F(UTEST_Detection, any_field_tells_the_detections_apart)
{
  EXPECT_FALSE(dog == (Detection{"cat", 0.84F, 137, 205, 181, 332}));
  EXPECT_FALSE(dog == (Detection{"dog", 0.85F, 137, 205, 181, 332}));
  EXPECT_FALSE(dog == (Detection{"dog", 0.84F, 138, 205, 181, 332}));
  EXPECT_FALSE(dog == (Detection{"dog", 0.84F, 137, 206, 181, 332}));
  EXPECT_FALSE(dog == (Detection{"dog", 0.84F, 137, 205, 182, 332}));
  EXPECT_FALSE(dog == (Detection{"dog", 0.84F, 137, 205, 181, 333}));
}
