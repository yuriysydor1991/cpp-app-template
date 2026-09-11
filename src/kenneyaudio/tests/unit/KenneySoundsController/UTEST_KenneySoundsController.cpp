#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/kenneyaudio/controller/KenneySoundsController.h"
#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/sounds/KenneySounds.h"

using namespace kenneyaudio;
using namespace testing;

namespace
{

/**
 * @brief The backend stand-in, so the controller is answered for without any
 * audio library at all.
 */
class MockSoundPlayer : public IKenneySoundPlayer
{
 public:
  MOCK_METHOD(bool, supports, (const std::string& extension),
              (const, override));
  MOCK_METHOD(bool, play, (const KenneySoundPtr& sound), (override));
};

}  // namespace

class UTEST_KenneySoundsController : public Test
{
 public:
  using MockSoundPlayerPtr = std::shared_ptr<MockSoundPlayer>;

  MockSoundPlayerPtr create_player()
  {
    return std::make_shared<NiceMock<MockSoundPlayer>>();
  }

  IKenneySoundsPtr sounds{KenneySounds::create()};
};

TEST_F(UTEST_KenneySoundsController, reports_a_backend_when_one_is_given)
{
  EXPECT_TRUE(
      KenneySoundsController::create(sounds, create_player())->playable());
}

TEST_F(UTEST_KenneySoundsController, reports_no_backend_when_none_is_given)
{
  EXPECT_FALSE(KenneySoundsController::create(sounds, nullptr)->playable());
}

TEST_F(UTEST_KenneySoundsController, draws_only_what_the_backend_decodes)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));
  ON_CALL(*player, supports("wav")).WillByDefault(Return(true));

  auto controller = KenneySoundsController::create(sounds, player);

  for (int draw = 0; draw < 32; ++draw) {
    auto sound = controller->draw();

    ASSERT_NE(sound, nullptr);
    EXPECT_EQ(sound->extension(), "wav");
  }
}

TEST_F(UTEST_KenneySoundsController, the_draw_follows_the_backend_of_the_day)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));
  ON_CALL(*player, supports("ogg")).WillByDefault(Return(true));

  auto controller = KenneySoundsController::create(sounds, player);

  for (int draw = 0; draw < 32; ++draw) {
    EXPECT_EQ(controller->draw()->extension(), "ogg");
  }
}

TEST_F(UTEST_KenneySoundsController, falls_back_when_the_backend_decodes_none)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));

  auto sound = KenneySoundsController::create(sounds, player)->draw();

  ASSERT_NE(sound, nullptr);
  EXPECT_NE(sounds->find(sound->pack()->name(), sound->path()), nullptr);
}

TEST_F(UTEST_KenneySoundsController, draws_of_the_whole_set_with_no_backend)
{
  auto controller = KenneySoundsController::create(sounds, nullptr);

  std::set<std::string> drawnAliases;

  for (int draw = 0; draw < 64; ++draw) {
    auto sound = controller->draw();

    ASSERT_NE(sound, nullptr);
    drawnAliases.insert(sound->alias());
  }

  EXPECT_GT(drawnAliases.size(), 1u);
}

TEST_F(UTEST_KenneySoundsController, an_empty_set_draws_nothing)
{
  auto controller =
      KenneySoundsController::create(KenneySounds::create(nullptr), nullptr);

  EXPECT_EQ(controller->draw(), nullptr);
}

TEST_F(UTEST_KenneySoundsController, hands_the_playing_over_to_the_backend)
{
  auto player = create_player();
  auto controller = KenneySoundsController::create(sounds, player);

  ON_CALL(*player, supports(_)).WillByDefault(Return(true));

  auto sound = controller->draw();

  ASSERT_NE(sound, nullptr);

  EXPECT_CALL(*player, play(sound)).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(controller->play(sound));
}

TEST_F(UTEST_KenneySoundsController, plays_nothing_with_no_backend_at_all)
{
  auto controller = KenneySoundsController::create(sounds, nullptr);

  EXPECT_FALSE(controller->play(controller->draw()));
}
