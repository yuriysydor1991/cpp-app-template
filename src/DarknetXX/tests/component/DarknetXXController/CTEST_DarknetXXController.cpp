#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

#include "src/DarknetXX/DarknetXXController.h"
#include "src/DarknetXX/weights/OrigWeights.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace darknetxxi;
using namespace testing;

/**
 * @brief Component test of the DarknetXXController with the darknetxx core
 * and the project logger.
 *
 * The YOLOv4-tiny network of the COCO data set, the weights of which the
 * configure downloads, detects the objects of the darknetxx sample image. The
 * test cases needing the weights skip themselves while they are not
 * downloaded.
 */
class CTEST_DarknetXXController : public Test
{
 public:
  CTEST_DarknetXXController()
  {
    std::ofstream truncating{logFile, std::ofstream::trunc};

    LOG_INIT(logFile, MACRO_LVL_TRACE, false);
  }

  /// @brief Reopens the log file to flush it, since the logger flushes the
  /// warnings and the errors alone, and gives the log written so far.
  std::string log_contents() const
  {
    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    std::stringstream contents;

    contents << std::ifstream{logFile}.rdbuf();

    return contents.str();
  }

  static bool downloaded() { return std::ifstream{WEIGHTS}.good(); }

  bool init() { return controller->init(CFG, OrigWeights{WEIGHTS}, NAMES); }

  inline static const std::string logFile{CTEST_DarknetXXController_DATA_DIR
                                          "/CTEST_DarknetXXController.log"};

  inline static constexpr const char* const CFG = CTEST_DarknetXXController_CFG;
  inline static constexpr const char* const WEIGHTS =
      CTEST_DarknetXXController_WEIGHTS;
  inline static constexpr const char* const NAMES =
      CTEST_DarknetXXController_NAMES;
  inline static constexpr const char* const IMAGE =
      CTEST_DarknetXXController_IMAGE;

  DarknetXXControllerPtr controller{DarknetXXController::create()};
};

TEST_F(CTEST_DarknetXXController, the_sample_image_objects_get_detected)
{
  if (!downloaded()) {
    GTEST_SKIP() << "No " << WEIGHTS << " weights file downloaded";
  }

  ASSERT_TRUE(init());

  const auto objects = controller->detect(IMAGE);

  ASSERT_TRUE(objects.has_value());
  EXPECT_THAT(*objects, IsSupersetOf({Field(&Detection::name, "dog"),
                                      Field(&Detection::name, "bicycle"),
                                      Field(&Detection::name, "truck")}));
  EXPECT_THAT(*objects, Each(Field(&Detection::probability,
                                   Gt(DarknetXXController::THRESHOLD))));
}

TEST_F(CTEST_DarknetXXController, the_darknetxx_messages_get_into_the_log)
{
  if (!downloaded()) {
    GTEST_SKIP() << "No " << WEIGHTS << " weights file downloaded";
  }

  ASSERT_TRUE(init());

  // the darknetxx info messages go a level down
  EXPECT_THAT(log_contents(),
              ContainsRegex("DBG [0-9]+ OrigWeightsReader.cpp:[0-9]+ : "
                            "Loading weights from"));
}

TEST_F(CTEST_DarknetXXController, the_darknetxx_errors_get_into_the_log)
{
  EXPECT_FALSE(controller->init(CTEST_DarknetXXController_DATA_DIR
                                "/an-absent.cfg",
                                OrigWeights{WEIGHTS}, NAMES));

  EXPECT_THAT(log_contents(),
              AllOf(ContainsRegex("ERR [0-9]+ NetworkSource.cpp:[0-9]+ : "
                                  "Couldn't open the network cfg file"),
                    ContainsRegex("ERR [0-9]+ DarknetXXController.cpp:[0-9]+ : "
                                  "Fail to load the network cfg file")));
}
