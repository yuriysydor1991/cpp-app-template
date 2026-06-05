#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <QGuiApplication>
#include <QVersionNumber>
#include <QVulkanInstance>
#include <QtGlobal>

#include "src/qtvulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"
#include "src/qtvulkan/device-info/PhysicalDeviceInfoHandler.h"

using namespace testing;
using namespace qtvulkani;

class CTEST_PhysicalDeviceInfoHandler : public Test
{
 public:
  DeviceInfoHandlerFactory factory;
};

TEST_F(CTEST_PhysicalDeviceInfoHandler, factory_creates_non_null_default_handler)
{
  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(CTEST_PhysicalDeviceInfoHandler, factory_default_handler_is_physical)
{
  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  EXPECT_NE(std::dynamic_pointer_cast<PhysicalDeviceInfoHandler>(handler),
            nullptr);
}

TEST_F(CTEST_PhysicalDeviceInfoHandler, device_type_to_string_maps_known_types)
{
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU),
            "discrete GPU");
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_CPU),
            "CPU");
}

TEST_F(CTEST_PhysicalDeviceInfoHandler, live_runtime_enumeration)
{
  QVulkanInstance instance;
  instance.setApiVersion(QVersionNumber(1, 0, 0));

  if (!instance.create()) {
    GTEST_SKIP() << "No usable Vulkan runtime is available in this environment";
  }

  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  ASSERT_NE(handler, nullptr);

  // Enumerating the physical devices of a freshly created instance must succeed
  // (zero reported devices is itself a valid, successful outcome).
  EXPECT_TRUE(handler->handle(&instance));
}

int main(int argc, char** argv)
{
  // QVulkanInstance needs a QGuiApplication with a platform plugin that supports
  // Vulkan. Default to the offscreen plugin when running headless so the test
  // binary starts (the live Vulkan case then skips), while still honoring a real
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
