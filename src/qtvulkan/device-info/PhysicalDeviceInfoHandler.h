#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFOHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFOHANDLER_CLASS_H

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"
#include "src/qtvulkan/device-info/PhysicalDeviceInfo.h"

class QVulkanInstance;

namespace qtvulkani
{

/**
 * @brief A device info handler that enumerates the Vulkan physical devices
 * reachable through the given QVulkanInstance (using the native Qt
 * QVulkanFunctions wrappers) and logs a few of their well known properties (the
 * device name, the device type, the supported API version, the driver version
 * and the vendor / device identifiers).
 */
class PhysicalDeviceInfoHandler : public IDeviceInfoHandler
{
 public:
  ~PhysicalDeviceInfoHandler() override = default;
  PhysicalDeviceInfoHandler() = default;

  /**
   * @brief Enumerates the physical devices through the given instance and logs
   * their properties.
   *
   * @param instance A valid, created QVulkanInstance.
   *
   * @return Returns true in case the enumeration succeeded (including the valid
   * case of zero reported devices) and false in case of any Vulkan error or an
   * invalid instance.
   */
  bool handle(QVulkanInstance* instance) override;

  /**
   * @brief Maps a VkPhysicalDeviceType enumerator to a human readable string.
   *
   * @param type The physical device type to describe.
   *
   * @return Returns the corresponding short description.
   */
  static std::string device_type_to_string(VkPhysicalDeviceType type);

 protected:
  /**
   * @brief Enumerates the physical devices and reads the well known properties
   * of each of them through the QVulkanInstance's QVulkanFunctions.
   *
   * This is the only method that actually talks to the Vulkan runtime and is
   * intentionally kept as a thin, overridable seam, so the handle() logging
   * orchestration may be unit tested without a live Vulkan runtime. The real
   * implementation is exercised by the component test against the system Vulkan
   * runtime.
   *
   * @param instance A valid, created QVulkanInstance.
   *
   * @return Returns the per device condensed properties.
   *
   * @throws std::runtime_error in case any of the Vulkan enumeration calls
   * fail.
   */
  virtual std::vector<PhysicalDeviceInfo> fetch_devices(
      QVulkanInstance* instance);
};

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PHYSICALDEVICEINFOHANDLER_CLASS_H
