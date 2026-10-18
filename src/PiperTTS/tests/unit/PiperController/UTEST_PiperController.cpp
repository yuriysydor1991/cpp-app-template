#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <piper.h>

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

#include "src/PiperTTS/PiperController.h"
#include "src/PiperTTS/tests/mocks/PiperLibrary/PiperLibraryMock.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"

using namespace pipertts;
using namespace testing;

/**
 * @brief Unit test of the PiperController over the mocked libpiper, so every
 * failure of the engine is at hand. The empty voice files stand for the voice
 * models, which the mocked library loads not.
 */
class UTEST_PiperController : public Test
{
 public:
  UTEST_PiperController()
  {
    for (const auto& model : {VOICE, OTHER_VOICE}) {
      std::ofstream{model};
      std::ofstream{model + ".json"};
    }
  }

  inline static const std::string TEXT{"Hello, Piper!"};
  inline static const std::string VOICE{UTEST_PiperController_DATA_DIR
                                        "/en_US-voice-medium.onnx"};
  inline static const std::string OTHER_VOICE{UTEST_PiperController_DATA_DIR
                                              "/uk_UA-voice-medium.onnx"};

  /// @brief Declared ahead of the controller, so it outlives the one and sees
  /// the voice freed.
  NiceMock<PiperLibraryMock> library;

  PiperController controller;
};

TEST_F(UTEST_PiperController, create_gives_a_piper_controller)
{
  EXPECT_NE(std::dynamic_pointer_cast<PiperController>(
                tts::ISpeechSynthesizer::create()),
            nullptr);
}

TEST_F(UTEST_PiperController, synthesis_converts_the_spoken_samples)
{
  EXPECT_CALL(library, Create(VOICE, EndsWith("/espeak-ng-data")));
  EXPECT_CALL(library, SynthesizeStart(TEXT));
  EXPECT_CALL(library, SynthesizeNext(NotNull()))
      .WillOnce([](auto* const chunk) {
        return PiperLibraryMock::speak(chunk, {0.5F, -1.0F}, false);
      })
      .WillOnce([](auto* const chunk) {
        return PiperLibraryMock::speak(chunk, {2.0F, -2.0F, 0.0F}, true);
      });

  const auto speech = controller.synthesize(TEXT, VOICE);

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_samples(),
            (tts::Speech::samples{16383, -32767, 32767, -32767, 0}));
  EXPECT_EQ(speech->get_sample_rate(), PiperLibraryMock::SAMPLE_RATE);
}

TEST_F(UTEST_PiperController, nothing_spoken_gives_an_empty_speech)
{
  const auto speech = controller.synthesize("", VOICE);

  ASSERT_TRUE(speech.has_value());
  EXPECT_TRUE(speech->get_samples().empty());
}

TEST_F(UTEST_PiperController, the_voice_is_loaded_once)
{
  EXPECT_CALL(library, Create(_, _)).Times(1);
  EXPECT_CALL(library, SynthesizeStart(_)).Times(2);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, another_voice_replaces_the_loaded_one)
{
  InSequence loading;

  EXPECT_CALL(library, Create(VOICE, _));
  EXPECT_CALL(library, Free(PiperLibraryMock::synthesizer()));
  EXPECT_CALL(library, Create(OTHER_VOICE, _));
  // The destruction frees the other voice.
  EXPECT_CALL(library, Free(PiperLibraryMock::synthesizer()));

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, OTHER_VOICE).has_value());
}

TEST_F(UTEST_PiperController, missing_voice_gives_nothing)
{
  EXPECT_CALL(library, Create(_, _)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, "nosuchvoice.onnx").has_value());
}

TEST_F(UTEST_PiperController, failed_load_gives_nothing)
{
  EXPECT_CALL(library, Create(_, _)).WillOnce(Return(nullptr));
  EXPECT_CALL(library, SynthesizeStart(_)).Times(0);
  EXPECT_CALL(library, Free(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, failed_load_is_retried)
{
  EXPECT_CALL(library, Create(_, _))
      .WillOnce(Return(nullptr))
      .WillOnce(Return(PiperLibraryMock::synthesizer()));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, library_exception_gives_nothing)
{
  EXPECT_CALL(library, Create(_, _))
      .WillOnce(Throw(std::runtime_error{"broken voice"}));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, failed_start_gives_nothing)
{
  EXPECT_CALL(library, SynthesizeStart(_)).WillOnce(Return(PIPER_ERR_GENERIC));
  EXPECT_CALL(library, SynthesizeNext(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, failed_synthesis_gives_nothing)
{
  EXPECT_CALL(library, SynthesizeNext(_)).WillOnce(Return(PIPER_ERR_GENERIC));

  EXPECT_FALSE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, destruction_frees_the_loaded_voice)
{
  EXPECT_CALL(library, Free(PiperLibraryMock::synthesizer())).Times(1);

  EXPECT_TRUE(controller.synthesize(TEXT, VOICE).has_value());
}

TEST_F(UTEST_PiperController, destruction_leaves_the_unused_engine_alone)
{
  EXPECT_CALL(library, Create(_, _)).Times(0);
  EXPECT_CALL(library, Free(_)).Times(0);
}
