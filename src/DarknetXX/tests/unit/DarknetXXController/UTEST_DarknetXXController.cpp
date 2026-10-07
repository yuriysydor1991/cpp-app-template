#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <zlib.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "src/DarknetXX/DarknetXXController.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/Dxxwjz2Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"

using namespace darknetxxi;
using namespace testing;

/**
 * @brief Unit test of the DarknetXXController over the darknetxx core with
 * the tiny network of the test's own: the maxpool of the whole image, the 1x1
 * convolution of no weights but the biases and the YOLO layer of the single
 * cell. The biases alone tell the YOLO layer outputs, so whatever the image,
 * the network detects the box of the anchor of the high objectness: the
 * centered square of the anchor size, the half or the quarter of the network
 * one. The dxxwjz2 files keep the network of the very cfg, the class of which
 * they name the WIDGET one.
 */
class UTEST_DarknetXXController : public Test
{
 public:
  UTEST_DarknetXXController()
  {
    std::ofstream{path(CFG)} << CFG_TEXT;
    std::ofstream{path(NAMES)} << THING << "\n";
    std::ofstream{path(NOT_AN_IMAGE)} << "not an image";

    cv::imwrite(path(IMAGE),
                cv::Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar::all(128)));

    write_weights(WEIGHTS, 0U);
    write_gzip(DXXWJZ1, dxxwjz1(0U));
    write_gzip(OTHER_DXXWJZ1, dxxwjz1(1U));
    std::ofstream{path(PLAIN_DXXWJZ1)} << dxxwjz1(0U);
    write_gzip(DXXWJZ2, dxxwjz2(0U));
    write_gzip(OTHER_DXXWJZ2, dxxwjz2(1U));
    write_gzip(NETWORK_DXXWJZ2, "{" + network_members() + "}");
  }

  static std::string path(const char* const name)
  {
    return std::string{UTEST_DarknetXXController_DATA_DIR} + "/" + name;
  }

  /// @brief The convolution biases: the x, y, w, h, objectness and class
  /// entries of every anchor, the high objectness of the given one alone.
  static std::vector<float> biases(const std::size_t anchor)
  {
    std::vector<float> values(ANCHORS * ENTRIES, 0.0F);

    for (std::size_t index = 0U; index < ANCHORS; ++index) {
      values[index * ENTRIES + OBJECTNESS] = index == anchor ? LOGIT : -LOGIT;
      values[index * ENTRIES + CLASS] = LOGIT;
    }

    return values;
  }

  /// @brief The original Darknet weights file: the version, the count of the
  /// seen images, the convolution biases and it's zero weights.
  static void write_weights(const char* const name, const std::size_t anchor)
  {
    static constexpr const std::array<std::int32_t, 3> version{0, 2, 5};
    static constexpr const std::uint64_t seen{0U};

    std::vector<float> values = biases(anchor);
    values.resize(values.size() + CONV_WEIGHTS, 0.0F);

    std::ofstream file{path(name), std::ios::binary};

    file.write(reinterpret_cast<const char*>(version.data()), sizeof(version));
    file.write(reinterpret_cast<const char*>(&seen), sizeof(seen));
    // The file keeps the floats of the very binary representation.
    // cppcheck-suppress invalidPointerCast
    file.write(reinterpret_cast<const char*>(values.data()),
               static_cast<std::streamsize>(values.size() * sizeof(float)));
  }

  /// @brief The dxxwjz1 document of the very arrays.
  static std::string dxxwjz1(const std::size_t anchor)
  {
    return document(R"("format": "dxxwjz1", "version": 1)", anchor);
  }

  /// @brief The dxxwjz2 document of the network and of the very arrays.
  static std::string dxxwjz2(const std::size_t anchor)
  {
    return document(network_members(), anchor);
  }

  /// @brief The leading dxxwjz2 members: the format, the version and the
  /// network of the cfg text and the class name.
  static std::string network_members()
  {
    return R"("format": "dxxwjz2", "version": 2, "network": {"cfg": )" +
           nlohmann::json(CFG_TEXT).dump() +
           R"(, "classes": [{"index": 0, "name": ")" + WIDGET + R"("}]})";
  }

  /// @brief The document of the given leading members and of the arrays.
  static std::string document(const std::string& members,
                              const std::size_t anchor)
  {
    std::ostringstream json;

    json << "{" << members << R"(, "header": {"major": 0, )"
         << R"("minor": 2, "revision": 5, "seen": 0}, "layers": [)"
         << R"({"index": 0, "type": "maxpool"}, {"index": 1, "type": )"
         << R"("convolutional", "arrays": {"biases": [)";

    const auto values = biases(anchor);

    for (std::size_t index = 0U; index < values.size(); ++index) {
      json << (index > 0U ? ", " : "") << values[index];
    }

    json << R"(], "weights": [0)";

    for (std::size_t index = 1U; index < CONV_WEIGHTS; ++index) {
      json << ", 0";
    }

    json << R"(]}}, {"index": 2, "type": "yolo"}]})";

    return json.str();
  }

  static void write_gzip(const char* const name, const std::string& text)
  {
    gzFile file = gzopen(path(name).c_str(), "wb");

    gzwrite(file, text.data(), static_cast<unsigned>(text.size()));
    gzclose(file);
  }

  /// @brief Matches the detection of the class and the box.
  static auto detected(const std::string& name, const int left, const int top,
                       const int width, const int height)
  {
    return AllOf(Field(&Detection::name, name),
                 Field(&Detection::probability, FloatNear(PROBABILITY, 1e-4F)),
                 Field(&Detection::left, left), Field(&Detection::top, top),
                 Field(&Detection::width, width),
                 Field(&Detection::height, height));
  }

  inline static constexpr const char* const CFG_TEXT =
      "[net]\nwidth=32\nheight=32\nchannels=3\n\n"
      "[maxpool]\nsize=32\nstride=32\n\n"
      "[convolutional]\nfilters=18\nsize=1\nstride=1\nactivation=linear\n\n"
      "[yolo]\nmask=0,1,2\nanchors=16,16, 8,8, 4,4\nclasses=1\nnum=3\n";
  inline static const std::string THING{"thing"};
  inline static const std::string WIDGET{"widget"};

  inline static constexpr const char* const CFG = "tiny.cfg";
  inline static constexpr const char* const NAMES = "tiny.names";
  inline static constexpr const char* const IMAGE = "image.png";
  inline static constexpr const char* const NOT_AN_IMAGE = "not-an-image.png";
  inline static constexpr const char* const WEIGHTS = "tiny.weights";
  inline static constexpr const char* const DXXWJZ1 = "tiny.dxxwjz1";
  inline static constexpr const char* const OTHER_DXXWJZ1 = "other.dxxwjz1";
  inline static constexpr const char* const PLAIN_DXXWJZ1 = "plain.dxxwjz1";
  inline static constexpr const char* const DXXWJZ2 = "tiny.dxxwjz2";
  inline static constexpr const char* const OTHER_DXXWJZ2 = "other.dxxwjz2";
  inline static constexpr const char* const NETWORK_DXXWJZ2 = "network.dxxwjz2";
  inline static constexpr const char* const ABSENT = "an-absent-file";

  inline static constexpr const std::size_t ANCHORS = 3U;
  inline static constexpr const std::size_t ENTRIES = 6U;
  inline static constexpr const std::size_t OBJECTNESS = 4U;
  inline static constexpr const std::size_t CLASS = 5U;
  inline static constexpr const std::size_t CONV_WEIGHTS = 18U * 3U;
  inline static constexpr const float LOGIT = 5.0F;
  /// @brief The objectness times the class probability, the logistic
  /// function of the LOGIT squared.
  inline static constexpr const float PROBABILITY = 0.98666F;
  inline static constexpr const int WIDTH = 64;
  inline static constexpr const int HEIGHT = 48;

  DarknetXXControllerPtr controller{DarknetXXController::create()};
};

TEST_F(UTEST_DarknetXXController, create_gives_an_instance)
{
  EXPECT_NE(DarknetXXController::create(), nullptr);
}

TEST_F(UTEST_DarknetXXController, nothing_is_detected_before_the_init)
{
  EXPECT_FALSE(controller->detect(path(IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController, an_absent_cfg_fails_the_init)
{
  EXPECT_FALSE(
      controller->init(path(ABSENT), OrigWeights{path(WEIGHTS)}, path(NAMES)));
  EXPECT_FALSE(controller->detect(path(IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController, absent_weights_files_fail_the_init)
{
  EXPECT_FALSE(
      controller->init(path(CFG), OrigWeights{path(ABSENT)}, path(NAMES)));
  EXPECT_FALSE(
      controller->init(path(CFG), Dxxwjz1Weights{path(ABSENT)}, path(NAMES)));
  EXPECT_FALSE(
      controller->init(path(CFG), Dxxwjz2Weights{path(ABSENT)}, path(NAMES)));
  EXPECT_FALSE(controller->detect(path(IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController, an_absent_names_file_fails_the_init)
{
  EXPECT_FALSE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(ABSENT)));
}

TEST_F(UTEST_DarknetXXController,
       a_dxxwjz1_file_given_as_the_original_weights_fails_the_init)
{
  EXPECT_FALSE(
      controller->init(path(CFG), OrigWeights{path(DXXWJZ1)}, path(NAMES)));
}

TEST_F(UTEST_DarknetXXController, the_original_weights_detect_the_object)
{
  ASSERT_TRUE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 16, 12, 32, 24))));
}

TEST_F(UTEST_DarknetXXController, the_dxxwjz1_weights_detect_the_same_object)
{
  ASSERT_TRUE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(NAMES)));

  const auto original = controller->detect(path(IMAGE));

  ASSERT_TRUE(
      controller->init(path(CFG), Dxxwjz1Weights{path(DXXWJZ1)}, path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              AllOf(Optional(SizeIs(1U)), Eq(original)));
}

TEST_F(UTEST_DarknetXXController,
       the_plain_json_dxxwjz1_weights_detect_the_same_object)
{
  ASSERT_TRUE(controller->init(path(CFG), Dxxwjz1Weights{path(PLAIN_DXXWJZ1)},
                               path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 16, 12, 32, 24))));
}

TEST_F(UTEST_DarknetXXController, the_dxxwjz1_arrays_are_the_loaded_ones)
{
  ASSERT_TRUE(controller->init(path(CFG), Dxxwjz1Weights{path(OTHER_DXXWJZ1)},
                               path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 24, 18, 16, 12))));
}

TEST_F(UTEST_DarknetXXController, the_classes_get_numbered_without_the_names)
{
  ASSERT_TRUE(controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, ""));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(Field(&Detection::name, "class 0"))));
}

TEST_F(UTEST_DarknetXXController, an_unreadable_image_fails_the_detection)
{
  ASSERT_TRUE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(NAMES)));

  EXPECT_FALSE(controller->detect(path(ABSENT)).has_value());
  EXPECT_FALSE(controller->detect(path(NOT_AN_IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController, a_failed_init_unloads_the_loaded_network)
{
  ASSERT_TRUE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(NAMES)));
  ASSERT_FALSE(
      controller->init(path(CFG), OrigWeights{path(ABSENT)}, path(NAMES)));

  EXPECT_FALSE(controller->detect(path(IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController, a_reloaded_network_replaces_the_loaded_one)
{
  ASSERT_TRUE(
      controller->init(path(CFG), OrigWeights{path(WEIGHTS)}, path(NAMES)));
  ASSERT_TRUE(controller->init(path(CFG), Dxxwjz1Weights{path(OTHER_DXXWJZ1)},
                               path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 24, 18, 16, 12))));
}

TEST_F(UTEST_DarknetXXController, the_dxxwjz2_file_alone_is_the_network)
{
  ASSERT_TRUE(
      controller->init(path(DXXWJZ2), Dxxwjz2Weights{path(DXXWJZ2)}, ""));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(WIDGET, 16, 12, 32, 24))));
}

TEST_F(UTEST_DarknetXXController, the_names_file_goes_over_the_dxxwjz2_names)
{
  ASSERT_TRUE(controller->init(path(DXXWJZ2), Dxxwjz2Weights{path(DXXWJZ2)},
                               path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 16, 12, 32, 24))));
}

TEST_F(UTEST_DarknetXXController, the_dxxwjz2_arrays_load_into_the_cfg_network)
{
  ASSERT_TRUE(
      controller->init(path(CFG), Dxxwjz2Weights{path(OTHER_DXXWJZ2)}, ""));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(WIDGET, 24, 18, 16, 12))));
}

TEST_F(UTEST_DarknetXXController, the_dxxwjz2_network_takes_the_other_weights)
{
  ASSERT_TRUE(controller->init(path(DXXWJZ2), Dxxwjz1Weights{path(DXXWJZ1)},
                               path(NAMES)));

  EXPECT_THAT(controller->detect(path(IMAGE)),
              Optional(ElementsAre(detected(THING, 16, 12, 32, 24))));
}

TEST_F(UTEST_DarknetXXController,
       a_dxxwjz2_network_of_no_weights_fails_the_init)
{
  EXPECT_FALSE(controller->init(path(NETWORK_DXXWJZ2),
                                Dxxwjz2Weights{path(NETWORK_DXXWJZ2)}, ""));
  EXPECT_FALSE(controller->detect(path(IMAGE)).has_value());
}

TEST_F(UTEST_DarknetXXController,
       a_dxxwjz1_file_given_as_the_dxxwjz2_one_fails_the_init)
{
  EXPECT_FALSE(
      controller->init(path(CFG), Dxxwjz2Weights{path(DXXWJZ1)}, path(NAMES)));
}
