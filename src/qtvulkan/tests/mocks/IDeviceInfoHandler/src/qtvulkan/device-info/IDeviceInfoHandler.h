#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

class QVulkanInstance;

namespace qtvulkani
{

/**
 * @brief GMock mock of the IDeviceInfoHandler interface, used by the
 * QtVulkanController unit test to drive the enumeration outcome without a live
 * Vulkan runtime.
 */
class IDeviceInfoHandler
{
 public:
  using IDeviceInfoHandlerPtr = std::shared_ptr<IDeviceInfoHandler>;

  virtual ~IDeviceInfoHandler() = default;
  IDeviceInfoHandler() = default;

  MOCK_METHOD(bool, handle, (QVulkanInstance * instance));
};

using IDeviceInfoHandlerPtr = IDeviceInfoHandler::IDeviceInfoHandlerPtr;

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
