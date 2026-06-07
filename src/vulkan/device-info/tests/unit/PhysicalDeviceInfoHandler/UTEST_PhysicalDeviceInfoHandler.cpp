#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

#include "src/vulkan/device-info/PhysicalDeviceInfoHandler.h"

using namespace testing;
using namespace vulkani;

namespace
{

/**
 * @brief A non-null, opaque Vulkan instance handle.
 *
 * It is never dereferenced because the fetch_devices() seam is overridden in
 * the test double below, so a real, created Vulkan instance (which would require
 * a live loader / driver) is not needed to drive handle().
 */
VkInstance fake_instance()
{
  static int placeholder{0};
  return reinterpret_cast<VkInstance>(&placeholder);
}

/**
 * @brief Test double that replaces the only loader-touching method with a
 * configurable callback, so the handle() logging orchestration can be exercised
 * in isolation, without a live Vulkan runtime.
 */
class TestablePhysicalDeviceInfoHandler : public PhysicalDeviceInfoHandler
{
 public:
  // Re-export the protected result type so the test bodies can name it.
  using PhysicalDeviceInfoHandler::PhysicalDeviceInfo;

  std::function<std::vector<PhysicalDeviceInfo>(VkInstance)> onFetchDevices;

 protected:
  std::vector<PhysicalDeviceInfo> fetch_devices(VkInstance instance) override
  {
    if (onFetchDevices) {
      return onFetchDevices(instance);
    }

    return {};
  }
};

}  // namespace

class UTEST_PhysicalDeviceInfoHandler : public Test
{
 public:
  TestablePhysicalDeviceInfoHandler handler;
};

TEST_F(UTEST_PhysicalDeviceInfoHandler, handle_returns_true_on_successful_fetch)
{
  VkInstance received = VK_NULL_HANDLE;

  handler.onFetchDevices = [&](VkInstance instance) {
    received = instance;

    TestablePhysicalDeviceInfoHandler::PhysicalDeviceInfo device;
    device.name = "Unit Test GPU";
    device.type = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    device.apiVersion = VK_MAKE_VERSION(1, 3, 0);
    device.driverVersion = 42;
    device.vendorID = 0x10DE;
    device.deviceID = 0x1234;

    return std::vector<TestablePhysicalDeviceInfoHandler::PhysicalDeviceInfo>{
        device};
  };

  EXPECT_TRUE(handler.handle(fake_instance()));
  EXPECT_EQ(received, fake_instance());
}

TEST_F(UTEST_PhysicalDeviceInfoHandler, handle_returns_true_on_empty_device_list)
{
  bool fetchCalled = false;

  handler.onFetchDevices = [&](VkInstance) {
    fetchCalled = true;
    return std::vector<
        TestablePhysicalDeviceInfoHandler::PhysicalDeviceInfo>{};
  };

  // Zero reported devices is a valid, successful enumeration outcome.
  EXPECT_TRUE(handler.handle(fake_instance()));
  EXPECT_TRUE(fetchCalled);
}

TEST_F(UTEST_PhysicalDeviceInfoHandler, handle_returns_false_on_enumeration_error)
{
  handler.onFetchDevices =
      [&](VkInstance)
      -> std::vector<TestablePhysicalDeviceInfoHandler::PhysicalDeviceInfo> {
    throw std::runtime_error("vkEnumeratePhysicalDevices failed");
  };

  EXPECT_FALSE(handler.handle(fake_instance()));
}

TEST_F(UTEST_PhysicalDeviceInfoHandler, handle_returns_false_on_null_instance)
{
  bool fetchCalled = false;

  handler.onFetchDevices = [&](VkInstance) {
    fetchCalled = true;
    return std::vector<
        TestablePhysicalDeviceInfoHandler::PhysicalDeviceInfo>{};
  };

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // VK_NULL_HANDLE guard inside handle() is what is being exercised here.
  EXPECT_FALSE(handler.handle(VK_NULL_HANDLE));
  EXPECT_FALSE(fetchCalled);
}

TEST_F(UTEST_PhysicalDeviceInfoHandler, device_type_to_string_maps_known_types)
{
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU),
            "integrated GPU");
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU),
            "discrete GPU");
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU),
            "virtual GPU");
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_CPU),
            "CPU");
  EXPECT_EQ(PhysicalDeviceInfoHandler::device_type_to_string(
                VK_PHYSICAL_DEVICE_TYPE_OTHER),
            "other");
}
