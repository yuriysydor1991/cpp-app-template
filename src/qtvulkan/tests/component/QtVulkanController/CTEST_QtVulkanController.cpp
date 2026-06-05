#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QGuiApplication>
#include <QVersionNumber>
#include <QVulkanInstance>
#include <QtGlobal>

#include "src/qtvulkan/QtVulkanController.h"

using namespace testing;
using namespace qtvulkani;

class CTEST_QtVulkanController : public Test
{
 public:
  /**
   * @brief Whether a usable Vulkan instance can be created in this environment.
   *
   * Mirrors what the controller's init() does, but with a throwaway probe
   * instance, so the test can branch on the runtime availability without
   * coupling to the controller under test. Requires the living QGuiApplication
   * created in main().
   */
  static bool vulkan_runtime_available()
  {
    QVulkanInstance probe;
    probe.setApiVersion(QVersionNumber(1, 0, 0));
    return probe.create();
  }
};

TEST_F(CTEST_QtVulkanController, create_reflects_runtime_availability)
{
  QtVulkanControllerPtr controller = QtVulkanController::create();

  if (vulkan_runtime_available()) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() reports the unavailable runtime, so create() returns an empty
    // pointer instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}

TEST_F(CTEST_QtVulkanController, run_against_live_runtime)
{
  if (!vulkan_runtime_available()) {
    GTEST_SKIP() << "No usable Vulkan runtime is available in this environment";
  }

  QtVulkanControllerPtr controller = QtVulkanController::create();

  ASSERT_NE(controller, nullptr);

  // With a usable Vulkan runtime the demo enumerates the physical devices (zero
  // is a valid, successful outcome) and must complete successfully.
  EXPECT_TRUE(controller->run());
}

int main(int argc, char** argv)
{
  // QVulkanInstance needs a QGuiApplication with a platform plugin that supports
  // Vulkan. Default to the offscreen plugin when running headless so the test
  // binary starts (the live Vulkan cases then skip), while still honoring a real
  // display when one is configured.
  if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM") &&
      qEnvironmentVariableIsEmpty("DISPLAY") &&
      qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY")) {
    qputenv("QT_QPA_PLATFORM", "offscreen");
  }

  QGuiApplication app(argc, argv);
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
