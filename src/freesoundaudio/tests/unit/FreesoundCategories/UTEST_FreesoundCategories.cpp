#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/freesoundaudio/categories/FreesoundCategories.h"

using namespace freesoundaudio;
using namespace testing;

class UTEST_FreesoundCategories : public Test
{
 public:
  IFreesoundCategoriesPtr categories{FreesoundCategories::create()};
};

TEST_F(UTEST_FreesoundCategories, carries_every_pack_of_the_index)
{
  EXPECT_EQ(categories->count(), 2u);
  EXPECT_EQ(categories->all().size(), categories->count());
}

TEST_F(UTEST_FreesoundCategories, the_packs_stay_ordered_by_the_name)
{
  ASSERT_EQ(categories->all().size(), 2u);

  EXPECT_EQ(categories->all().front()->name(), "impact-sounds");
  EXPECT_EQ(categories->all().back()->name(), "interface-sounds");
}

TEST_F(UTEST_FreesoundCategories, finds_a_pack_by_it_s_name)
{
  auto found = categories->find("interface-sounds");

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->name(), "interface-sounds");
}

TEST_F(UTEST_FreesoundCategories, gives_no_pack_of_an_unknown_name)
{
  EXPECT_EQ(categories->find("no-such-category"), nullptr);
}
