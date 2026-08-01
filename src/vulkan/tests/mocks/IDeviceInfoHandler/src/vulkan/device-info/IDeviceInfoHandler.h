#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H

#include <gmock/gmock.h>
#include <vulkan/vulkan.h>

#include <memory>

namespace vulkani
{

/**
 * @brief GMock mock of the IDeviceInfoHandler interface, used by the
 * VulkanController unit test to drive the enumeration call outcome without a
 * live Vulkan runtime.
 */
class IDeviceInfoHandler
{
 public:
  using IDeviceInfoHandlerPtr = std::shared_ptr<IDeviceInfoHandler>;

  virtual ~IDeviceInfoHandler() = default;
  IDeviceInfoHandler() = default;

  MOCK_METHOD(bool, handle, (VkInstance instance));
};

using IDeviceInfoHandlerPtr = IDeviceInfoHandler::IDeviceInfoHandlerPtr;

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
