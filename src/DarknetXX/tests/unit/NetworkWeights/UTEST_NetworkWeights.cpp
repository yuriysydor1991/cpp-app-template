#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/DarknetXX/tests/unit/NetworkWeights/WeightsLoaderMock.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/Dxxwjz2Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"

using namespace darknetxxi;
using namespace testing;

/**
 * @brief Unit test of the network weights files, which load by the loader
 * method of their own format.
 */
class UTEST_NetworkWeights : public Test
{
 public:
  inline static const std::string WEIGHTS{"/tmp/a.weights"};
  inline static const std::string DXXWJZ1{"/tmp/a.dxxwjz1"};
  inline static const std::string DXXWJZ2{"/tmp/a.dxxwjz2"};

  StrictMock<WeightsLoaderMock> loader;
  const OrigWeights orig{WEIGHTS};
  const Dxxwjz1Weights dxxwjz1{DXXWJZ1};
  const Dxxwjz2Weights dxxwjz2{DXXWJZ2};
};

TEST_F(UTEST_NetworkWeights, the_files_keep_their_paths)
{
  EXPECT_EQ(orig.path(), WEIGHTS);
  EXPECT_EQ(dxxwjz1.path(), DXXWJZ1);
  EXPECT_EQ(dxxwjz2.path(), DXXWJZ2);
}

TEST_F(UTEST_NetworkWeights, the_original_weights_load_by_their_method)
{
  EXPECT_CALL(loader, load(Matcher<const OrigWeights&>(Ref(orig))))
      .WillOnce(Return(true));

  EXPECT_TRUE(orig.load_into(loader));
}

TEST_F(UTEST_NetworkWeights, the_dxxwjz1_weights_load_by_their_method)
{
  EXPECT_CALL(loader, load(Matcher<const Dxxwjz1Weights&>(Ref(dxxwjz1))))
      .WillOnce(Return(true));

  EXPECT_TRUE(dxxwjz1.load_into(loader));
}

TEST_F(UTEST_NetworkWeights, the_dxxwjz2_weights_load_by_their_method)
{
  EXPECT_CALL(loader, load(Matcher<const Dxxwjz2Weights&>(Ref(dxxwjz2))))
      .WillOnce(Return(true));

  EXPECT_TRUE(dxxwjz2.load_into(loader));
}

TEST_F(UTEST_NetworkWeights, a_failed_load_fails_the_files)
{
  EXPECT_CALL(loader, load(An<const OrigWeights&>())).WillOnce(Return(false));
  EXPECT_CALL(loader, load(An<const Dxxwjz1Weights&>()))
      .WillOnce(Return(false));
  EXPECT_CALL(loader, load(An<const Dxxwjz2Weights&>()))
      .WillOnce(Return(false));

  EXPECT_FALSE(orig.load_into(loader));
  EXPECT_FALSE(dxxwjz1.load_into(loader));
  EXPECT_FALSE(dxxwjz2.load_into(loader));
}
