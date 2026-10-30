#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "src/STT/ISpeechRecognizer.h"
#include "src/SherpaONNX/SherpaONNXController.h"
#include "src/SherpaONNX/tests/mocks/SherpaONNXLibrary/SherpaONNXLibraryMock.h"

using namespace sherpaonnx;
using namespace testing;

/**
 * @brief Unit test of the SherpaONNXController over the mocked sherpa-onnx
 * library, so every failure of the engine is at hand. The model directory
 * keeps empty files, since the mock loads none of them.
 */
class UTEST_SherpaONNXController : public Test
{
 public:
  using Config = sherpa_onnx::cxx::OfflineRecognizerConfig;
  using ModelConfig = sherpa_onnx::cxx::OfflineModelConfig;
  using TransducerConfig = sherpa_onnx::cxx::OfflineTransducerModelConfig;

  UTEST_SherpaONNXController()
  {
    std::filesystem::create_directories(MODEL);

    for (const auto* const file :
         {"encoder.int8.onnx", "decoder.onnx", "decoder.int8.onnx",
          "joiner.int8.onnx", "tokens.txt"}) {
      std::ofstream{MODEL + "/" + file};
    }
  }

  static sherpa_onnx::cxx::OfflineRecognizerResult text(const char* const text)
  {
    sherpa_onnx::cxx::OfflineRecognizerResult result;

    result.text = text;

    return result;
  }

  inline static const std::string MODEL{UTEST_SherpaONNXController_DATA_DIR
                                        "/transducer"};
  inline static const std::vector<float> AUDIO{0.0F, 0.5F, -0.5F};

  /// @brief Declared ahead of the controller, so it outlives the one and sees
  /// the engine destruction.
  NiceMock<SherpaONNXLibraryMock> library;

  SherpaONNXController controller;
};

TEST_F(UTEST_SherpaONNXController, create_gives_a_sherpa_onnx_controller)
{
  EXPECT_NE(std::dynamic_pointer_cast<SherpaONNXController>(
                stt::ISpeechRecognizer::create()),
            nullptr);
}

TEST_F(UTEST_SherpaONNXController, init_configures_the_model_files)
{
  EXPECT_CALL(
      library,
      Create(Field(&Config::model_config,
                   AllOf(Field(&ModelConfig::transducer,
                               AllOf(Field(&TransducerConfig::encoder,
                                           MODEL + "/encoder.int8.onnx"),
                                     Field(&TransducerConfig::decoder,
                                           MODEL + "/decoder.onnx"),
                                     Field(&TransducerConfig::joiner,
                                           MODEL + "/joiner.int8.onnx"))),
                         Field(&ModelConfig::tokens, MODEL + "/tokens.txt"),
                         Field(&ModelConfig::model_type, "nemo_transducer"),
                         Field(&ModelConfig::num_threads, Ge(1))))));

  EXPECT_TRUE(controller.init(MODEL));
}

TEST_F(UTEST_SherpaONNXController, failed_load_fails_the_init)
{
  EXPECT_CALL(library, Create(_)).WillOnce(Return(false));
  EXPECT_CALL(library, Destroy()).Times(0);
  EXPECT_CALL(library, Decode()).Times(0);

  EXPECT_FALSE(controller.init(MODEL));
  EXPECT_FALSE(controller.recognize(AUDIO).has_value());
}

TEST_F(UTEST_SherpaONNXController, failed_load_drops_the_previous_model)
{
  EXPECT_CALL(library, Create(_))
      .WillOnce(Return(true))
      .WillOnce(Return(false));
  EXPECT_CALL(library, Destroy()).Times(1);

  EXPECT_TRUE(controller.init(MODEL));
  EXPECT_FALSE(controller.init(MODEL));
  EXPECT_FALSE(controller.recognize(AUDIO).has_value());
}

TEST_F(UTEST_SherpaONNXController, nothing_is_recognized_before_the_init)
{
  EXPECT_CALL(library, Decode()).Times(0);

  EXPECT_FALSE(controller.recognize(AUDIO).has_value());
}

TEST_F(UTEST_SherpaONNXController, recognition_decodes_the_audio)
{
  {
    InSequence order;

    EXPECT_CALL(library,
                AcceptWaveform(stt::ISpeechRecognizer::SAMPLE_RATE, AUDIO));
    EXPECT_CALL(library, Decode());
    EXPECT_CALL(library, GetResult()).WillOnce(Return(text("Hello")));
  }

  ASSERT_TRUE(controller.init(MODEL));

  EXPECT_EQ(controller.recognize(AUDIO), "Hello");
}

TEST_F(UTEST_SherpaONNXController, recognition_strips_the_spaces_around)
{
  EXPECT_CALL(library, GetResult())
      .WillOnce(Return(text(" Hello, world! ")))
      .WillOnce(Return(text("  ")));

  ASSERT_TRUE(controller.init(MODEL));

  EXPECT_EQ(controller.recognize(AUDIO), "Hello, world!");
  EXPECT_EQ(controller.recognize(AUDIO), "");
}

TEST_F(UTEST_SherpaONNXController, a_reloaded_model_replaces_the_loaded_one)
{
  EXPECT_CALL(library, Create(_)).Times(2);
  EXPECT_CALL(library, Destroy()).Times(2);

  EXPECT_TRUE(controller.init(MODEL));
  EXPECT_TRUE(controller.init(MODEL));
  EXPECT_EQ(controller.recognize(AUDIO), "");
}

TEST_F(UTEST_SherpaONNXController, destruction_leaves_the_unused_engine_alone)
{
  EXPECT_CALL(library, Create(_)).Times(0);
  EXPECT_CALL(library, Destroy()).Times(0);
}
