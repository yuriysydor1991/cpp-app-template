#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <memory>

#include "src/STT/ISpeechRecognizer.h"
#include "src/STT/Microphone.h"
#include "src/STT/SpeechListener.h"
#include "src/STT/tests/mocks/ISpeechRecognizer/ISpeechRecognizerMock.h"

using namespace stt;
using namespace testing;

namespace stt
{

ISpeechRecognizerPtr ISpeechRecognizer::create()
{
  return std::make_shared<NiceMock<ISpeechRecognizerMock>>();
}

}  // namespace stt

/**
 * @brief Unit test of the SpeechListener over the mocked Microphone and
 * ISpeechRecognizer.
 */
class UTEST_SpeechListener : public Test
{
 public:
  using samples = ISpeechRecognizer::samples;

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

  inline static constexpr const char* const MODEL = "a-model";
  inline static constexpr const std::size_t RATE =
      ISpeechRecognizer::SAMPLE_RATE;
  inline static constexpr const float TONE_STEP =
      2.0F * 3.14159265F * 440.0F / static_cast<float>(RATE);

  const std::shared_ptr<NiceMock<ISpeechRecognizerMock>> recognizer{
      std::make_shared<NiceMock<ISpeechRecognizerMock>>()};
  const std::shared_ptr<NiceMock<Microphone>> microphone{
      std::make_shared<NiceMock<Microphone>>()};

  SpeechListener listener{recognizer, microphone};
};

TEST_F(UTEST_SpeechListener, create_gives_an_instance)
{
  EXPECT_NE(SpeechListener::create(), nullptr);
}

TEST_F(UTEST_SpeechListener, init_loads_the_model_of_the_recognizer)
{
  EXPECT_CALL(*recognizer, init(MODEL)).WillOnce(Return(true));

  EXPECT_TRUE(listener.init(MODEL));
}

TEST_F(UTEST_SpeechListener, nothing_is_heard_before_the_init)
{
  EXPECT_CALL(*microphone, open(_)).Times(0);
  EXPECT_CALL(*microphone, read()).Times(0);

  EXPECT_FALSE(listener.listen().has_value());
}

TEST_F(UTEST_SpeechListener, nothing_is_heard_after_a_failed_init)
{
  EXPECT_CALL(*recognizer, init(_)).WillOnce(Return(false));
  EXPECT_CALL(*microphone, open(_)).Times(0);

  EXPECT_FALSE(listener.init(MODEL));
  EXPECT_FALSE(listener.listen().has_value());
}

TEST_F(UTEST_SpeechListener, listening_opens_the_microphone_at_the_engine_rate)
{
  EXPECT_CALL(*microphone, open(ISpeechRecognizer::SAMPLE_RATE))
      .Times(2)
      .WillRepeatedly(Return(true));
  EXPECT_CALL(*microphone, read())
      .Times(2)
      .WillRepeatedly(Return(samples(RATE / 10U, 0.0F)));
  EXPECT_CALL(*recognizer, recognize(_)).Times(0);

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_EQ(listener.listen(), "");
  EXPECT_EQ(listener.listen(), "");
}

TEST_F(UTEST_SpeechListener, listening_fails_with_the_microphone)
{
  EXPECT_CALL(*microphone, open(_)).WillOnce(Return(false));
  EXPECT_CALL(*microphone, read()).Times(0);

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_FALSE(listener.listen().has_value());
}

TEST_F(UTEST_SpeechListener, listening_recognizes_the_heard_utterance)
{
  EXPECT_CALL(*microphone, read())
      .WillOnce(Return(utterance()))
      .WillRepeatedly(Return(samples{}));

  // the lead, the second of the tone and the pause ending it, which is less
  // than all of the heard audio
  EXPECT_CALL(*recognizer, recognize(SizeIs(AllOf(Gt(RATE), Lt(3U * RATE)))))
      .WillOnce(Return(ISpeechRecognizer::result{"heard"}));

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_EQ(listener.listen(), "heard");
  EXPECT_EQ(listener.listen(), "");
}

TEST_F(UTEST_SpeechListener, listening_fails_with_the_recognition)
{
  EXPECT_CALL(*microphone, read()).WillOnce(Return(utterance()));
  EXPECT_CALL(*recognizer, recognize(_))
      .WillOnce(Return(ISpeechRecognizer::result{}));

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_FALSE(listener.listen().has_value());
}
