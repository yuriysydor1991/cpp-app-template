#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/opengameartaudio/controller/OpenGameArtSoundsController.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

using namespace opengameartaudio;
using namespace testing;

namespace
{

/**
 * @brief The backend stand-in, so the controller is answered for without any
 * audio library at all.
 */
class MockSoundPlayer : public IOpenGameArtSoundPlayer
{
 public:
  MOCK_METHOD(bool, supports, (const std::string& extension),
              (const, override));
  MOCK_METHOD(bool, play, (const OpenGameArtSoundPtr& sound), (override));
};

}  // namespace

class UTEST_OpenGameArtSoundsController : public Test
{
 public:
  using MockSoundPlayerPtr = std::shared_ptr<MockSoundPlayer>;

  MockSoundPlayerPtr create_player()
  {
    return std::make_shared<NiceMock<MockSoundPlayer>>();
  }

  IOpenGameArtSoundsPtr sounds{OpenGameArtSounds::create()};
};

TEST_F(UTEST_OpenGameArtSoundsController, reports_a_backend_when_one_is_given)
{
  EXPECT_TRUE(
      OpenGameArtSoundsController::create(sounds, create_player())->playable());
}

TEST_F(UTEST_OpenGameArtSoundsController, reports_no_backend_when_none_is_given)
{
  EXPECT_FALSE(
      OpenGameArtSoundsController::create(sounds, nullptr)->playable());
}

TEST_F(UTEST_OpenGameArtSoundsController, draws_only_what_the_backend_decodes)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));
  ON_CALL(*player, supports("wav")).WillByDefault(Return(true));

  auto controller = OpenGameArtSoundsController::create(sounds, player);

  for (int draw = 0; draw < 32; ++draw) {
    auto sound = controller->draw();

    ASSERT_NE(sound, nullptr);
    EXPECT_EQ(sound->extension(), "wav");
  }
}

TEST_F(UTEST_OpenGameArtSoundsController,
       the_draw_follows_the_backend_of_the_day)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));
  ON_CALL(*player, supports("ogg")).WillByDefault(Return(true));

  auto controller = OpenGameArtSoundsController::create(sounds, player);

  for (int draw = 0; draw < 32; ++draw) {
    EXPECT_EQ(controller->draw()->extension(), "ogg");
  }
}

TEST_F(UTEST_OpenGameArtSoundsController,
       falls_back_when_the_backend_decodes_none)
{
  auto player = create_player();

  ON_CALL(*player, supports(_)).WillByDefault(Return(false));

  auto sound = OpenGameArtSoundsController::create(sounds, player)->draw();

  ASSERT_NE(sound, nullptr);
  EXPECT_NE(sounds->find(sound->pack()->name(), sound->path()), nullptr);
}

TEST_F(UTEST_OpenGameArtSoundsController,
       draws_of_the_whole_set_with_no_backend)
{
  auto controller = OpenGameArtSoundsController::create(sounds, nullptr);

  std::set<std::string> drawnAliases;

  for (int draw = 0; draw < 64; ++draw) {
    auto sound = controller->draw();

    ASSERT_NE(sound, nullptr);
    drawnAliases.insert(sound->alias());
  }

  EXPECT_GT(drawnAliases.size(), 1u);
}

TEST_F(UTEST_OpenGameArtSoundsController, an_empty_set_draws_nothing)
{
  auto controller = OpenGameArtSoundsController::create(
      OpenGameArtSounds::create(nullptr), nullptr);

  EXPECT_EQ(controller->draw(), nullptr);
}

TEST_F(UTEST_OpenGameArtSoundsController, hands_the_playing_over_to_the_backend)
{
  auto player = create_player();
  auto controller = OpenGameArtSoundsController::create(sounds, player);

  ON_CALL(*player, supports(_)).WillByDefault(Return(true));

  auto sound = controller->draw();

  ASSERT_NE(sound, nullptr);

  EXPECT_CALL(*player, play(sound)).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(controller->play(sound));
}

TEST_F(UTEST_OpenGameArtSoundsController, plays_nothing_with_no_backend_at_all)
{
  auto controller = OpenGameArtSoundsController::create(sounds, nullptr);

  EXPECT_FALSE(controller->play(controller->draw()));
}
