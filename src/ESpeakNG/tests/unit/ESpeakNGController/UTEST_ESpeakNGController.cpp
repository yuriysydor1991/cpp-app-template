#include <espeak-ng/espeak_ng.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/ESpeakNG/ESpeakNGController.h"
#include "src/ESpeakNG/tests/mocks/ESpeakNGLibrary/ESpeakNGLibraryMock.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"

using namespace espeakng;
using namespace testing;

/**
 * @brief Unit test of the ESpeakNGController over the mocked eSpeak NG
 * library, so every failure of the engine is at hand.
 */
class UTEST_ESpeakNGController : public Test
{
 public:
  inline static const std::string TEXT{"Привіт, світе!"};
  inline static const std::string VOICE{"uk"};

  /// @brief Declared ahead of the controller, so it outlives the one and sees
  /// the termination of it.
  NiceMock<ESpeakNGLibraryMock> library;

  ESpeakNGController controller;
};

TEST_F(UTEST_ESpeakNGController, create_gives_an_espeak_ng_controller)
{
  EXPECT_NE(std::dynamic_pointer_cast<ESpeakNGController>(
                tts::ISpeechSynthesizer::create()),
            nullptr);
}

TEST_F(UTEST_ESpeakNGController, synthesis_collects_the_spoken_samples)
{
  EXPECT_CALL(library, InitializeOutput(ENOUTPUT_MODE_SYNCHRONOUS));
  EXPECT_CALL(library, SetVoiceByName(VOICE));
  EXPECT_CALL(library,
              Synthesize(TEXT, TEXT.size() + 1U, espeakCHARS_UTF8, NotNull()))
      .WillOnce([](const std::string&, std::size_t, unsigned int,
                   void* const userData) {
        ESpeakNGLibraryMock::speak({1, -2, 3}, userData);
        ESpeakNGLibraryMock::speak({4, 5}, userData);
        ESpeakNGLibraryMock::speak({}, userData);
        return ENS_OK;
      });

  const auto speech = controller.synthesize(TEXT, VOICE);

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_samples(), (tts::Speech::samples{1, -2, 3, 4, 5}));
  EXPECT_EQ(speech->get_sample_rate(), ESpeakNGLibraryMock::SAMPLE_RATE);
}

TEST_F(UTEST_ESpeakNGController, nothing_spoken_gives_an_empty_speech)
{
  const auto speech = controller.synthesize("", VOICE);

  ASSERT_TRUE(speech.has_value());
  EXPECT_TRUE(speech->get_samples().empty());
}

TEST_F(UTEST_ESpeakNGController, the_engine_is_initialized_once)
{
  EXPECT_CALL(library, Initialize()).Times(1);
  EXPECT_CALL(library, Synthesize(_, _, _, _)).Times(2);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, "en").has_value());
}

TEST_F(UTEST_ESpeakNGController, failed_init_gives_nothing)
{
  EXPECT_CALL(library, Initialize()).WillOnce(Return(ENS_VERSION_MISMATCH));
  EXPECT_CALL(library, InitializeOutput(_)).Times(0);
  EXPECT_CALL(library, SetVoiceByName(_)).Times(0);
  EXPECT_CALL(library, Terminate()).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_ESpeakNGController, failed_init_is_retried)
{
  EXPECT_CALL(library, Initialize())
      .WillOnce(Return(ENS_VERSION_MISMATCH))
      .WillOnce(Return(ENS_OK));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_ESpeakNGController, failed_output_init_terminates_the_engine)
{
  EXPECT_CALL(library, InitializeOutput(_)).WillOnce(Return(ENS_NOT_SUPPORTED));
  EXPECT_CALL(library, SetVoiceByName(_)).Times(0);
  EXPECT_CALL(library, Terminate()).Times(1);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_ESpeakNGController, unknown_voice_gives_nothing)
{
  EXPECT_CALL(library, SetVoiceByName("nosuchvoice"))
      .WillOnce(Return(ENS_VOICE_NOT_FOUND));
  EXPECT_CALL(library, Synthesize(_, _, _, _)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, "nosuchvoice").has_value());
}

TEST_F(UTEST_ESpeakNGController, failed_synthesis_gives_nothing)
{
  EXPECT_CALL(library, Synthesize(_, _, _, _))
      .WillOnce(Return(ENS_UNKNOWN_TEXT_ENCODING));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_ESpeakNGController, destruction_terminates_the_initialized_engine)
{
  EXPECT_CALL(library, Terminate()).Times(1);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_ESpeakNGController, destruction_leaves_the_unused_engine_alone)
{
  EXPECT_CALL(library, Initialize()).Times(0);
  EXPECT_CALL(library, Terminate()).Times(0);
}
