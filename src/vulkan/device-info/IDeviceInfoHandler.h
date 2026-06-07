#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H

#include <memory>

#include <vulkan/vulkan.h>

namespace vulkani
{

/**
 * @brief Interface for the Vulkan device information handlers.
 *
 * A device info handler encapsulates a single, self contained interaction with
 * an already created Vulkan instance (enumerating the physical devices, reading
 * their properties, etc.). The owning VulkanController is responsible for
 * creating the instance and passing it down to the handler. This keeps the
 * instance life cycle and the concrete query logic decoupled and independently
 * testable.
 *
 * The handle() method takes the raw VkInstance handle (which is itself an opaque
 * pointer) rather than the owning controller, so the handler stays free of the
 * instance ownership concerns and is trivially testable with a fake handle.
 */
class IDeviceInfoHandler
{
 public:
  using IDeviceInfoHandlerPtr = std::shared_ptr<IDeviceInfoHandler>;

  virtual ~IDeviceInfoHandler() = default;
  IDeviceInfoHandler() = default;

  /**
   * @brief Execute the handler's query against the given, already created,
   * Vulkan instance.
   *
   * @param instance A valid, created Vulkan instance handle owned by the caller.
   * Must not be a VK_NULL_HANDLE.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool handle(VkInstance instance) = 0;
};

using IDeviceInfoHandlerPtr = IDeviceInfoHandler::IDeviceInfoHandlerPtr;

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
