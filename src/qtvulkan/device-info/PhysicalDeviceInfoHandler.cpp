#include "src/qtvulkan/device-info/PhysicalDeviceInfoHandler.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include <QVulkanFunctions>
#include <QVulkanInstance>
#include <vulkan/vulkan.h>

#include "src/log/log.h"

namespace qtvulkani
{

bool PhysicalDeviceInfoHandler::handle(QVulkanInstance* instance)
{
  if (instance == nullptr) {
    LOGE("No valid Qt Vulkan instance provided");
    return false;
  }

  try {
    const std::vector<PhysicalDeviceInfo> devices = fetch_devices(instance);

    LOGI("Detected " << devices.size() << " Vulkan physical device(s)");

    for (std::size_t i = 0; i < devices.size(); ++i) {
      const PhysicalDeviceInfo& device = devices[i];

      LOGI("Physical device #" << i << ": " << device.name);
      LOGI("  type        : " << device_type_to_string(device.type));
      LOGI("  API version : " << VK_VERSION_MAJOR(device.apiVersion) << "."
                              << VK_VERSION_MINOR(device.apiVersion) << "."
                              << VK_VERSION_PATCH(device.apiVersion));
      LOGI("  driver ver. : " << device.driverVersion);
      LOGI("  vendor ID   : " << device.vendorID);
      LOGI("  device ID   : " << device.deviceID);
    }
  }
  catch (const std::exception& e) {
    LOGE("Vulkan physical device enumeration error: " << e.what());
    return false;
  }

  return true;
}

std::vector<PhysicalDeviceInfoHandler::PhysicalDeviceInfo>
PhysicalDeviceInfoHandler::fetch_devices(QVulkanInstance* instance)
{
  // The native Qt QVulkanFunctions wrapper resolves and dispatches the core
  // instance level Vulkan commands for the underlying VkInstance handle.
  QVulkanFunctions* functions = instance->functions();

  if (functions == nullptr) {
    throw std::runtime_error("QVulkanInstance::functions() returned null");
  }

  const VkInstance vkInstance = instance->vkInstance();

  std::uint32_t count = 0;

  VkResult result =
      functions->vkEnumeratePhysicalDevices(vkInstance, &count, nullptr);

  if (result != VK_SUCCESS && result != VK_INCOMPLETE) {
    throw std::runtime_error(
        "vkEnumeratePhysicalDevices (count query) failed with the VkResult "
        "code: " +
        std::to_string(static_cast<int>(result)));
  }

  std::vector<VkPhysicalDevice> handles(count, VK_NULL_HANDLE);

  if (count > 0) {
    result = functions->vkEnumeratePhysicalDevices(vkInstance, &count,
                                                   handles.data());

    if (result != VK_SUCCESS && result != VK_INCOMPLETE) {
      throw std::runtime_error(
          "vkEnumeratePhysicalDevices (device query) failed with the VkResult "
          "code: " +
          std::to_string(static_cast<int>(result)));
    }
  }

  std::vector<PhysicalDeviceInfo> devices;
  devices.reserve(handles.size());

  for (const VkPhysicalDevice handle : handles) {
    VkPhysicalDeviceProperties props{};
    functions->vkGetPhysicalDeviceProperties(handle, &props);

    PhysicalDeviceInfo info;
    info.name = props.deviceName;
    info.type = props.deviceType;
    info.apiVersion = props.apiVersion;
    info.driverVersion = props.driverVersion;
    info.vendorID = props.vendorID;
    info.deviceID = props.deviceID;

    devices.push_back(info);
  }

  return devices;
}

std::string PhysicalDeviceInfoHandler::device_type_to_string(
    VkPhysicalDeviceType type)
{
  switch (type) {
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
      return "integrated GPU";
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
      return "discrete GPU";
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
      return "virtual GPU";
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
      return "CPU";
    case VK_PHYSICAL_DEVICE_TYPE_OTHER:
    default:
      return "other";
  }
}

}  // namespace qtvulkani
