#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/kenneyaudio/packs/KenneyPacks.h"

using namespace kenneyaudio;
using namespace testing;

class UTEST_KenneyPacks : public Test
{
 public:
  IKenneyPacksPtr packs{KenneyPacks::create()};
};

TEST_F(UTEST_KenneyPacks, carries_every_pack_of_the_index)
{
  EXPECT_EQ(packs->count(), 2u);
  EXPECT_EQ(packs->all().size(), packs->count());
}

TEST_F(UTEST_KenneyPacks, the_packs_stay_ordered_by_the_name)
{
  ASSERT_EQ(packs->all().size(), 2u);

  EXPECT_EQ(packs->all().front()->name(), "impact-sounds");
  EXPECT_EQ(packs->all().back()->name(), "interface-sounds");
}

TEST_F(UTEST_KenneyPacks, finds_a_pack_by_it_s_name)
{
  auto found = packs->find("interface-sounds");

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->name(), "interface-sounds");
}

TEST_F(UTEST_KenneyPacks, gives_no_pack_of_an_unknown_name)
{
  EXPECT_EQ(packs->find("no-such-pack"), nullptr);
}
