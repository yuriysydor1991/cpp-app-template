#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "project-global-decls.h"
#include "src/TTS/AudioPlayer.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/WavWriter.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace tts;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override
  {
    ISpeechSynthesizer::onMockCreate = nullptr;
    AudioPlayer::onMockCreate = nullptr;
    WavWriter::onMockCreate = nullptr;
  }

  /// @brief Makes the mocked synthesizer expect the given text and voice.
  static void expect_synthesis(const std::string& text,
                               const std::string& voice)
  {
    ISpeechSynthesizer::onMockCreate =
        [text, voice](ISpeechSynthesizer& synthesizer) {
          EXPECT_CALL(synthesizer, synthesize(text, voice));
        };
  }

  /// @brief Makes the mocked player expect the given count of the playbacks.
  static void expect_playbacks(const int count)
  {
    AudioPlayer::onMockCreate = [count](AudioPlayer& player) {
      EXPECT_CALL(player, play(_, _)).Times(count);
    };
  }

  /// @brief Makes the mocked writer expect the given count of the writings.
  static void expect_writings(const int count)
  {
    WavWriter::onMockCreate = [count](WavWriter& writer) {
      EXPECT_CALL(writer, write(_, _)).Times(count);
    };
  }

  inline static const std::string TEXT{"Привіт, світе!"};
  inline static const std::string VOICE{"uk"};
  inline static const std::string OUTPUT{"/tmp/a-speech.wav"};

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_Application, speaks_the_default_text_with_the_default_voice)
{
  expect_synthesis(project_decls::PROJECT_TTS_TEXT,
                   project_decls::PROJECT_TTS_VOICE);
  expect_playbacks(1);
  expect_writings(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, speaks_the_text_and_the_voice_of_the_parameters)
{
  appCtx->set_text(TEXT);
  appCtx->set_voice(VOICE);

  expect_synthesis(TEXT, VOICE);
  expect_playbacks(1);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, writes_the_speech_into_the_output_file)
{
  appCtx->set_output_path(OUTPUT);

  WavWriter::onMockCreate = [](WavWriter& writer) {
    EXPECT_CALL(writer,
                write(Property(&Speech::get_samples, Speech::samples{1, 2, 3}),
                      OUTPUT));
  };
  expect_playbacks(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_writing_fails_the_run)
{
  appCtx->set_output_path(OUTPUT);

  WavWriter::onMockCreate = [](WavWriter& writer) {
    EXPECT_CALL(writer, write(_, _)).WillOnce(Return(false));
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_synthesis_outputs_nothing)
{
  ISpeechSynthesizer::onMockCreate = [](ISpeechSynthesizer& synthesizer) {
    EXPECT_CALL(synthesizer, synthesize(_, _))
        .WillOnce(Return(ISpeechSynthesizer::result{}));
  };
  expect_playbacks(0);
  expect_writings(0);

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_playback_fails_the_run)
{
  AudioPlayer::onMockCreate = [](AudioPlayer& player) {
    EXPECT_CALL(player, play(_, _)).WillOnce(Return(false));
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, the_stop_flag_stops_the_playback)
{
  AudioPlayer::onMockCreate = [this](AudioPlayer& player) {
    EXPECT_CALL(player, play(_, _))
        .WillOnce(
            [this](const Speech&, const AudioPlayer::stop_check& stopped) {
              EXPECT_FALSE(stopped());
              appCtx->set_stop(true);
              EXPECT_TRUE(stopped());
              return true;
            });
  };

  EXPECT_EQ(app->run(appCtx), 0);
}
