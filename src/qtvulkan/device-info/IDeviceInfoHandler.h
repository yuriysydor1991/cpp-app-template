#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H

#include <memory>

class QVulkanInstance;

namespace qtvulkani
{

/**
 * @brief Interface for the Qt Vulkan device information handlers.
 *
 * A device info handler encapsulates a single, self contained interaction with
 * an already created QVulkanInstance (enumerating the physical devices, reading
 * their properties, etc.). The owning QtVulkanController creates the instance
 * and passes it down to the handler. This keeps the instance life cycle and the
 * concrete query logic decoupled and independently testable.
 *
 * The handle() method takes the raw QVulkanInstance pointer (owned by the
 * caller) rather than the owning controller, so the handler stays free of the
 * instance ownership concerns and is trivially testable with a fake pointer.
 */
class IDeviceInfoHandler
{
 public:
  using IDeviceInfoHandlerPtr = std::shared_ptr<IDeviceInfoHandler>;

  virtual ~IDeviceInfoHandler() = default;
  IDeviceInfoHandler() = default;

  /**
   * @brief Execute the handler's query against the given, already created,
   * Qt Vulkan instance.
   *
   * @param instance A valid, created QVulkanInstance owned by the caller. Must
   * not be a nullptr.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool handle(QVulkanInstance* instance) = 0;
};

using IDeviceInfoHandlerPtr = IDeviceInfoHandler::IDeviceInfoHandlerPtr;

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDEVICEINFOHANDLER_CLASS_H
