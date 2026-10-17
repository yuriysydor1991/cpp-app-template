#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/opengameartaudio/packs/OpenGameArtPacks.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtPacks : public Test
{
 public:
  IOpenGameArtPacksPtr packs{OpenGameArtPacks::create()};
};

TEST_F(UTEST_OpenGameArtPacks, carries_every_pack_of_the_index)
{
  EXPECT_EQ(packs->count(), 2u);
  EXPECT_EQ(packs->all().size(), packs->count());
}

TEST_F(UTEST_OpenGameArtPacks, the_packs_stay_ordered_by_the_name)
{
  ASSERT_EQ(packs->all().size(), 2u);

  EXPECT_EQ(packs->all().front()->name(), "impact-sounds");
  EXPECT_EQ(packs->all().back()->name(), "interface-sounds");
}

TEST_F(UTEST_OpenGameArtPacks, finds_a_pack_by_it_s_name)
{
  auto found = packs->find("interface-sounds");

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->name(), "interface-sounds");
}

TEST_F(UTEST_OpenGameArtPacks, gives_no_pack_of_an_unknown_name)
{
  EXPECT_EQ(packs->find("no-such-pack"), nullptr);
}

TEST_F(UTEST_OpenGameArtPacks, every_pack_carries_it_s_recorded_license)
{
  EXPECT_EQ(packs->find("interface-sounds")->license(), "CC0-1.0");
  EXPECT_EQ(packs->find("impact-sounds")->license(), "CC-BY-3.0");
}
