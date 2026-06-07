#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <vulkan/vulkan.h>

#include "src/vulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/vulkan/device-info/IDeviceInfoHandler.h"
#include "src/vulkan/device-info/PhysicalDeviceInfoHandler.h"

using namespace testing;
using namespace vulkani;

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
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  VkInstance instance = VK_NULL_HANDLE;

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    GTEST_SKIP() << "No usable Vulkan runtime is available in this environment";
  }

  ASSERT_NE(instance, VK_NULL_HANDLE);

  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  ASSERT_NE(handler, nullptr);

  // Enumerating the physical devices of a freshly created instance must succeed
  // (zero reported devices is itself a valid, successful outcome).
  EXPECT_TRUE(handler->handle(instance));

  vkDestroyInstance(instance, nullptr);
}
