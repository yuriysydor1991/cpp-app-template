#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <string>

#include "src/SherpaONNX/KokoroModel.h"
#include "src/SherpaONNX/SherpaONNXModel.h"
#include "src/SherpaONNX/VitsModel.h"

using namespace sherpaonnx;
using namespace testing;

/**
 * @brief Unit test of the SherpaONNXModel kinds detection and of the
 * sherpa-onnx configurations of the KokoroModel and the VitsModel. The model
 * directories mimic the sherpa-onnx tts-models release archives with empty
 * files.
 */
class UTEST_SherpaONNXModel : public Test
{
 public:
  /// @brief Creates the model directory of the given files, the ones ending
  /// with the slash as the directories.
  static std::string model_of(const std::string& name,
                              const std::initializer_list<std::string> files)
  {
    const std::string directory{UTEST_SherpaONNXModel_DATA_DIR "/" + name};

    std::filesystem::remove_all(directory);
    std::filesystem::create_directories(directory);

    for (const auto& file : files) {
      if (file.back() == '/') {
        std::filesystem::create_directories(directory + "/" + file);
      } else {
        std::ofstream{directory + "/" + file};
      }
    }

    return directory;
  }
};

TEST_F(UTEST_SherpaONNXModel, multilingual_kokoro_takes_the_us_and_zh_lexicons)
{
  const auto dir = model_of(
      "kokoro-int8-multi-lang-v1_0",
      {"model.int8.onnx", "voices.bin", "tokens.txt", "espeak-ng-data/",
       "lexicon-us-en.txt", "lexicon-gb-en.txt", "lexicon-zh.txt"});

  const auto model = SherpaONNXModel::detect(dir);

  ASSERT_NE(dynamic_cast<const KokoroModel*>(model.get()), nullptr);

  const auto config = model->configure();

  EXPECT_EQ(config.model.kokoro.model, dir + "/model.int8.onnx");
  EXPECT_EQ(config.model.kokoro.voices, dir + "/voices.bin");
  EXPECT_EQ(config.model.kokoro.tokens, dir + "/tokens.txt");
  EXPECT_EQ(config.model.kokoro.data_dir, dir + "/espeak-ng-data");
  EXPECT_EQ(config.model.kokoro.lexicon,
            dir + "/lexicon-us-en.txt," + dir + "/lexicon-zh.txt");
  EXPECT_TRUE(config.model.vits.model.empty());
  EXPECT_GE(config.model.num_threads, 1);
}

TEST_F(UTEST_SherpaONNXModel, english_kokoro_takes_no_lexicon)
{
  const auto dir =
      model_of("kokoro-en-v0_19",
               {"model.onnx", "voices.bin", "tokens.txt", "espeak-ng-data/"});

  const auto config = SherpaONNXModel::detect(dir)->configure();

  EXPECT_EQ(config.model.kokoro.model, dir + "/model.onnx");
  EXPECT_TRUE(config.model.kokoro.lexicon.empty());
}

TEST_F(UTEST_SherpaONNXModel, piper_voice_is_a_vits_model_named_by_the_voice)
{
  const auto dir = model_of("vits-piper-en_US-amy-low",
                            {"en_US-amy-low.onnx", "en_US-amy-low.onnx.json",
                             "tokens.txt", "espeak-ng-data/"});

  const auto model = SherpaONNXModel::detect(dir);

  ASSERT_NE(dynamic_cast<const VitsModel*>(model.get()), nullptr);

  const auto config = model->configure();

  EXPECT_EQ(config.model.vits.model, dir + "/en_US-amy-low.onnx");
  EXPECT_EQ(config.model.vits.tokens, dir + "/tokens.txt");
  EXPECT_EQ(config.model.vits.data_dir, dir + "/espeak-ng-data");
  EXPECT_TRUE(config.model.vits.lexicon.empty());
  EXPECT_TRUE(config.model.kokoro.model.empty());
}

TEST_F(UTEST_SherpaONNXModel, melo_takes_the_model_onnx_and_the_lexicon)
{
  const auto dir = model_of(
      "vits-melo-tts-zh_en",
      {"model.int8.onnx", "model.onnx", "tokens.txt", "lexicon.txt", "dict/"});

  const auto config = SherpaONNXModel::detect(dir)->configure();

  EXPECT_EQ(config.model.vits.model, dir + "/model.onnx");
  EXPECT_EQ(config.model.vits.lexicon, dir + "/lexicon.txt");
  EXPECT_TRUE(config.model.vits.data_dir.empty());
}

TEST_F(UTEST_SherpaONNXModel, directory_of_no_tokens_keeps_no_model)
{
  EXPECT_EQ(SherpaONNXModel::detect(model_of("no-tokens", {"model.onnx"})),
            nullptr);
  EXPECT_EQ(SherpaONNXModel::detect(UTEST_SherpaONNXModel_DATA_DIR "/none"),
            nullptr);
}
