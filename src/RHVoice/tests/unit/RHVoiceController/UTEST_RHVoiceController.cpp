#include <RHVoice.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/RHVoice/RHVoiceController.h"
#include "src/RHVoice/tests/mocks/RHVoiceLibrary/RHVoiceLibraryMock.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"

using namespace rhvoice;
using namespace testing;

/**
 * @brief Unit test of the RHVoiceController over the mocked RHVoice library,
 * so every failure of the engine is at hand.
 */
class UTEST_RHVoiceController : public Test
{
 public:
  inline static const std::string TEXT{"Привіт, світе!"};
  inline static const std::string VOICE{"Anatol"};

  /// @brief Declared ahead of the controller, so it outlives the one and sees
  /// the engine deletion.
  NiceMock<RHVoiceLibraryMock> library;

  RHVoiceController controller;
};

TEST_F(UTEST_RHVoiceController, create_gives_an_rhvoice_controller)
{
  EXPECT_NE(std::dynamic_pointer_cast<RHVoiceController>(
                tts::ISpeechSynthesizer::create()),
            nullptr);
}

TEST_F(UTEST_RHVoiceController, engine_takes_the_installed_data_and_callbacks)
{
  EXPECT_CALL(
      library,
      NewTtsEngine(AllOf(Field(&RHVoice_init_params::data_path, IsNull()),
                         Field(&RHVoice_init_params::config_path, IsNull()),
                         Field(&RHVoice_init_params::resource_paths, IsNull()),
                         Field(&RHVoice_init_params::options, 0U))));

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_NE(RHVoiceLibraryMock::callbacks.set_sample_rate, nullptr);
  EXPECT_NE(RHVoiceLibraryMock::callbacks.play_speech, nullptr);
  EXPECT_EQ(RHVoiceLibraryMock::callbacks.done, nullptr);
}

TEST_F(UTEST_RHVoiceController, synthesis_collects_the_spoken_samples)
{
  void* userData{nullptr};

  EXPECT_CALL(
      library,
      NewMessage(
          RHVoiceLibraryMock::ENGINE, TEXT, RHVoice_message_text,
          AllOf(Field(&RHVoice_synth_params::voice_profile, StrEq(VOICE)),
                Field(&RHVoice_synth_params::relative_rate, 1.0),
                Field(&RHVoice_synth_params::relative_pitch, 1.0),
                Field(&RHVoice_synth_params::relative_volume, 1.0)),
          NotNull()))
      .WillOnce(
          DoAll(SaveArg<4>(&userData), Return(RHVoiceLibraryMock::MESSAGE)));
  EXPECT_CALL(library, Speak(RHVoiceLibraryMock::MESSAGE))
      .WillOnce([&userData] {
        const int rate = RHVoiceLibraryMock::SAMPLE_RATE;

        EXPECT_NE(RHVoiceLibraryMock::speak(rate, {1, -2, 3}, userData), 0);
        EXPECT_NE(RHVoiceLibraryMock::speak(rate, {4, 5}, userData), 0);
        return 1;
      });
  EXPECT_CALL(library, DeleteMessage(RHVoiceLibraryMock::MESSAGE));

  const auto speech = controller.synthesize(TEXT, VOICE);

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_samples(), (tts::Speech::samples{1, -2, 3, 4, 5}));
  EXPECT_EQ(speech->get_sample_rate(), RHVoiceLibraryMock::SAMPLE_RATE);
}

TEST_F(UTEST_RHVoiceController, the_engine_is_created_once)
{
  EXPECT_CALL(library, NewTtsEngine(_)).Times(1);
  EXPECT_CALL(library, Speak(_)).Times(2);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, "Alan").has_value());
}

TEST_F(UTEST_RHVoiceController, failed_init_gives_nothing)
{
  EXPECT_CALL(library, NewTtsEngine(_)).WillOnce(Return(nullptr));
  EXPECT_CALL(library, NewMessage(_, _, _, _, _)).Times(0);
  EXPECT_CALL(library, DeleteTtsEngine(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_RHVoiceController, failed_init_is_retried)
{
  EXPECT_CALL(library, NewTtsEngine(_))
      .WillOnce(Return(nullptr))
      .WillOnce(Return(RHVoiceLibraryMock::ENGINE));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_RHVoiceController, unknown_voice_gives_nothing)
{
  EXPECT_CALL(library, NewMessage(_, _, _, _, _)).WillOnce(Return(nullptr));
  EXPECT_CALL(library, Speak(_)).Times(0);
  EXPECT_CALL(library, DeleteMessage(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, "nosuchvoice").has_value());
}

TEST_F(UTEST_RHVoiceController, failed_synthesis_gives_nothing)
{
  EXPECT_CALL(library, Speak(_)).WillOnce(Return(0));
  EXPECT_CALL(library, DeleteMessage(RHVoiceLibraryMock::MESSAGE)).Times(1);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_RHVoiceController, destruction_deletes_the_created_engine)
{
  EXPECT_CALL(library, DeleteTtsEngine(RHVoiceLibraryMock::ENGINE)).Times(1);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_RHVoiceController, destruction_leaves_the_unused_engine_alone)
{
  EXPECT_CALL(library, NewTtsEngine(_)).Times(0);
  EXPECT_CALL(library, DeleteTtsEngine(_)).Times(0);
}
