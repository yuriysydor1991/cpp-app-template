#include "src/qtvulkan/device-info/DeviceInfoHandlerFactory.h"

#include <memory>

#include "src/log/log.h"
#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"
#include "src/qtvulkan/device-info/PhysicalDeviceInfoHandler.h"

namespace qtvulkani
{

IDeviceInfoHandlerPtr DeviceInfoHandlerFactory::create_physical_device_handler()
{
  return std::make_shared<PhysicalDeviceInfoHandler>();
}

IDeviceInfoHandlerPtr DeviceInfoHandlerFactory::create_default_handler()
{
  LOGT("Creating the default (physical device) Qt Vulkan device info handler");

  return create_physical_device_handler();
}

}  // namespace qtvulkani
