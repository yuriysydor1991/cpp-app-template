#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <fstream>
#include <string>

#include "src/WhisperCPP/Microphone.h"
#include "src/WhisperCPP/WhisperController.h"
#include "src/WhisperCPP/tests/unit/WhisperController/WhisperControllerSpy.h"

using namespace whisperi;
using namespace testing;

/**
 * @brief Unit test of the WhisperController over the mocked Microphone.
 *
 * The real whisper.cpp loads the empty model of the whisper.cpp own tests, the
 * one holding no weights, so it transcribes no text at all. The test cases
 * needing that model skip themselves while it is not downloaded.
 */
class UTEST_WhisperController : public Test
{
 public:
  using samples = WhisperController::samples;

  ~UTEST_WhisperController() override { Microphone::onMockCreate = nullptr; }

  static bool has_test_model() { return std::ifstream{TEST_MODEL}.good(); }

  /// @brief A second of the 440 Hz tone, which the UtteranceDetector takes
  /// for the speech, between the seconds of the silence.
  static samples utterance()
  {
    samples audio(3U * RATE, 0.0F);

    for (std::size_t index = RATE; index < 2U * RATE; ++index) {
      audio[index] = 0.1F * std::sin(TONE_STEP * static_cast<float>(index));
    }

    return audio;
  }

  inline static constexpr const char* const TEST_MODEL =
      UTEST_WhisperController_MODEL;
  inline static constexpr const char* const ABSENT_MODEL =
      "an-absent-model.bin";
  inline static constexpr const std::size_t RATE = 16000U;
  inline static constexpr const float TONE_STEP =
      2.0F * 3.14159265F * 440.0F / static_cast<float>(RATE);
};

TEST_F(UTEST_WhisperController, create_gives_an_instance)
{
  EXPECT_NE(WhisperController::create(), nullptr);
}

TEST_F(UTEST_WhisperController, nothing_is_heard_before_the_init)
{
  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, open(_)).Times(0);
    EXPECT_CALL(microphone, read()).Times(0);
  };

  auto controller = WhisperController::create();

  EXPECT_FALSE(controller->listen().has_value());
  EXPECT_FALSE(controller->transcribe(samples(RATE, 0.0F)).has_value());
}

TEST_F(UTEST_WhisperController, an_absent_model_fails_the_init)
{
  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, open(_)).Times(0);
  };

  auto controller = WhisperController::create();

  EXPECT_FALSE(controller->init(ABSENT_MODEL, "auto"));
  EXPECT_FALSE(controller->listen().has_value());
}

TEST_F(UTEST_WhisperController, an_unknown_language_fails_the_init)
{
  auto controller = WhisperController::create();

  EXPECT_FALSE(controller->init(TEST_MODEL, "nosuchlanguage"));
  EXPECT_FALSE(controller->transcribe(samples(RATE, 0.0F)).has_value());
}

TEST_F(UTEST_WhisperController, a_model_without_weights_transcribes_no_text)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  auto controller = WhisperController::create();

  ASSERT_TRUE(controller->init(TEST_MODEL, "en"));

  EXPECT_EQ(controller->transcribe(utterance()), "");
  EXPECT_EQ(controller->transcribe({}), "");
}

TEST_F(UTEST_WhisperController, a_reloaded_model_replaces_the_loaded_one)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  auto controller = WhisperController::create();

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));
  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_EQ(controller->transcribe(utterance()), "");
}

TEST_F(UTEST_WhisperController,
       listening_opens_the_microphone_at_the_whisper_rate)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, open(static_cast<int>(RATE)))
        .Times(2)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(microphone, read())
        .Times(2)
        .WillRepeatedly(Return(samples(RATE / 10U, 0.0F)));
  };

  auto controller = WhisperController::create();

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_EQ(controller->listen(), "");
  EXPECT_EQ(controller->listen(), "");
}

TEST_F(UTEST_WhisperController, listening_fails_with_the_microphone)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, open(_)).WillOnce(Return(false));
    EXPECT_CALL(microphone, read()).Times(0);
  };

  auto controller = WhisperController::create();

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_FALSE(controller->listen().has_value());
}

TEST_F(UTEST_WhisperController, listening_transcribes_the_heard_utterance)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, read())
        .WillOnce(Return(utterance()))
        .WillRepeatedly(Return(samples{}));
  };

  WhisperControllerSpy controller;

  ASSERT_TRUE(controller.init(TEST_MODEL, "auto"));

  // the lead, the second of the tone and the pause ending it, which is less
  // than all of the heard audio
  EXPECT_CALL(controller, transcribe(SizeIs(AllOf(Gt(RATE), Lt(3U * RATE)))))
      .WillOnce(Return(WhisperController::result{"heard"}));

  EXPECT_EQ(controller.listen(), "heard");
  EXPECT_EQ(controller.listen(), "");
}

TEST_F(UTEST_WhisperController, listening_fails_with_the_transcription)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  Microphone::onMockCreate = [](Microphone& microphone) {
    EXPECT_CALL(microphone, read()).WillOnce(Return(utterance()));
  };

  WhisperControllerSpy controller;

  ASSERT_TRUE(controller.init(TEST_MODEL, "auto"));

  EXPECT_CALL(controller, transcribe(_))
      .WillOnce(Return(WhisperController::result{}));

  EXPECT_FALSE(controller.listen().has_value());
}
