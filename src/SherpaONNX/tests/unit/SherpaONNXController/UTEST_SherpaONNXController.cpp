#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "src/SherpaONNX/SherpaONNXController.h"
#include "src/SherpaONNX/tests/mocks/SherpaONNXLibrary/SherpaONNXLibraryMock.h"
#include "src/TTS/ISpeechSynthesizer.h"
#include "src/TTS/Speech.h"

using namespace sherpaonnx;
using namespace testing;

/**
 * @brief Unit test of the SherpaONNXController over the mocked sherpa-onnx
 * library, so every failure of the engine is at hand. The model directories
 * keep empty files, since the mock loads none of them.
 */
class UTEST_SherpaONNXController : public Test
{
 public:
  UTEST_SherpaONNXController()
  {
    for (const auto& model : {KOKORO, OTHER_KOKORO}) {
      std::filesystem::create_directories(model);
      std::ofstream{model + "/voices.bin"};
      std::ofstream{model + "/tokens.txt"};
    }
  }

  inline static const std::string TEXT{"Hello, sherpa-onnx!"};
  inline static const std::string KOKORO{UTEST_SherpaONNXController_DATA_DIR
                                         "/kokoro"};
  inline static const std::string OTHER_KOKORO{
      UTEST_SherpaONNXController_DATA_DIR "/other-kokoro"};

  /// @brief Declared ahead of the controller, so it outlives the one and sees
  /// the engine destruction.
  NiceMock<SherpaONNXLibraryMock> library;

  SherpaONNXController controller;
};

TEST_F(UTEST_SherpaONNXController, create_gives_a_sherpa_onnx_controller)
{
  EXPECT_NE(std::dynamic_pointer_cast<SherpaONNXController>(
                tts::ISpeechSynthesizer::create()),
            nullptr);
}

TEST_F(UTEST_SherpaONNXController, synthesis_converts_the_generated_samples)
{
  EXPECT_CALL(
      library,
      Create(Field(
          &sherpa_onnx::cxx::OfflineTtsConfig::model,
          Field(&sherpa_onnx::cxx::OfflineTtsModelConfig::kokoro,
                Field(&sherpa_onnx::cxx::OfflineTtsKokoroModelConfig::voices,
                      KOKORO + "/voices.bin")))));
  EXPECT_CALL(library, Generate(TEXT, 0, 1.0F))
      .WillOnce(Return(sherpa_onnx::cxx::GeneratedAudio{
          {0.0F, 0.5F, -1.0F, 2.0F, -2.0F}, 16000}));

  const auto speech = controller.synthesize(TEXT, KOKORO);

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_samples(),
            (tts::Speech::samples{0, 16384, -32767, 32767, -32767}));
  EXPECT_EQ(speech->get_sample_rate(), 16000);
}

TEST_F(UTEST_SherpaONNXController, nothing_generated_gives_an_empty_speech)
{
  const auto speech = controller.synthesize("", KOKORO);

  ASSERT_TRUE(speech.has_value());
  EXPECT_TRUE(speech->get_samples().empty());
  EXPECT_EQ(speech->get_sample_rate(), SherpaONNXLibraryMock::SAMPLE_RATE);
}

TEST_F(UTEST_SherpaONNXController, voice_suffix_selects_the_speaker)
{
  EXPECT_CALL(library, Generate(TEXT, 9, _));

  EXPECT_TRUE(controller.synthesize(TEXT, KOKORO + ":9").has_value());
}

TEST_F(UTEST_SherpaONNXController, unknown_speaker_gives_nothing)
{
  EXPECT_CALL(library, Generate(_, _, _)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO + ":10").has_value());
}

TEST_F(UTEST_SherpaONNXController, non_numeric_suffix_is_the_part_of_the_dir)
{
  EXPECT_CALL(library, Create(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO + ":x").has_value());
  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO + ":").has_value());
  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO + ":-1").has_value());
}

TEST_F(UTEST_SherpaONNXController, the_model_is_loaded_once_per_directory)
{
  EXPECT_CALL(library, Create(_)).Times(2);
  EXPECT_CALL(library, Destroy()).Times(2);
  EXPECT_CALL(library, Generate(_, _, _)).Times(4);

  EXPECT_TRUE(controller.synthesize(TEXT, KOKORO).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, KOKORO + ":1").has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, OTHER_KOKORO).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, OTHER_KOKORO).has_value());
}

TEST_F(UTEST_SherpaONNXController, directory_of_no_model_gives_nothing)
{
  EXPECT_CALL(library, Create(_)).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, "/no/such/model").has_value());
}

TEST_F(UTEST_SherpaONNXController, failed_load_gives_nothing)
{
  EXPECT_CALL(library, Create(_)).WillOnce(Return(false));
  EXPECT_CALL(library, Generate(_, _, _)).Times(0);
  EXPECT_CALL(library, Destroy()).Times(0);

  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO).has_value());
}

TEST_F(UTEST_SherpaONNXController, failed_load_is_retried)
{
  EXPECT_CALL(library, Create(_))
      .WillOnce(Return(false))
      .WillOnce(Return(true));

  EXPECT_FALSE(controller.synthesize(TEXT, KOKORO).has_value());
  EXPECT_TRUE(controller.synthesize(TEXT, KOKORO).has_value());
}

TEST_F(UTEST_SherpaONNXController, failed_load_drops_the_previous_model)
{
  EXPECT_CALL(library, Create(_))
      .WillOnce(Return(true))
      .WillOnce(Return(false));
  EXPECT_CALL(library, Destroy()).Times(1);

  EXPECT_TRUE(controller.synthesize(TEXT, KOKORO).has_value());
  EXPECT_FALSE(controller.synthesize(TEXT, OTHER_KOKORO).has_value());
  EXPECT_FALSE(controller.synthesize(TEXT, "/no/such/model").has_value());
}

TEST_F(UTEST_SherpaONNXController, destruction_leaves_the_unused_engine_alone)
{
  EXPECT_CALL(library, Create(_)).Times(0);
  EXPECT_CALL(library, Destroy()).Times(0);
}
