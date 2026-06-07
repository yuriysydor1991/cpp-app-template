#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H

#include "src/vulkan/device-info/IDeviceInfoHandler.h"

namespace vulkani
{

/**
 * @brief A factory that creates the Vulkan device information handler
 * instances.
 *
 * For now the factory exposes a single concrete handler (the physical device
 * one) and returns it as the default handler. New device info handlers are
 * meant to be added here as the project grows.
 */
class DeviceInfoHandlerFactory
{
 public:
  virtual ~DeviceInfoHandlerFactory() = default;
  DeviceInfoHandlerFactory() = default;

  /**
   * @brief Creates the physical device enumeration / info handler.
   *
   * @return Returns the created handler instance.
   */
  virtual IDeviceInfoHandlerPtr create_physical_device_handler();

  /**
   * @brief Creates the default device info handler.
   *
   * For now this is the physical device info handler.
   *
   * @return Returns the created default handler instance.
   */
  virtual IDeviceInfoHandlerPtr create_default_handler();
};

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H
