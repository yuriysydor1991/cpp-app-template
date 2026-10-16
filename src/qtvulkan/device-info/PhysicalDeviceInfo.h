#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFO_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFO_CLASS_H

#include <vulkan/vulkan.h>

#include <cstdint>
#include <string>

namespace qtvulkani
{

/**
 * @brief The condensed set of properties read for a single physical device.
 */
struct PhysicalDeviceInfo
{
  std::string name;
  VkPhysicalDeviceType type{VK_PHYSICAL_DEVICE_TYPE_OTHER};
  std::uint32_t apiVersion{0};
  std::uint32_t driverVersion{0};
  std::uint32_t vendorID{0};
  std::uint32_t deviceID{0};
};

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFO_CLASS_H
