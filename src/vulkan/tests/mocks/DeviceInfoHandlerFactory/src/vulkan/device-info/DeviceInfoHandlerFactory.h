#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H

#include <gmock/gmock.h>

#include <functional>

#include "src/vulkan/device-info/IDeviceInfoHandler.h"

namespace vulkani
{

/**
 * @brief GMock mock of the DeviceInfoHandlerFactory. The controller constructs
 * the factory internally, so an onMockCreate seam (the same idiom as the app
 * component mocks) lets a test configure each created instance.
 */
class DeviceInfoHandlerFactory
{
 public:
  virtual ~DeviceInfoHandlerFactory() = default;

  DeviceInfoHandlerFactory()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  MOCK_METHOD(IDeviceInfoHandlerPtr, create_physical_device_handler, ());
  MOCK_METHOD(IDeviceInfoHandlerPtr, create_default_handler, ());

  inline static std::function<void(DeviceInfoHandlerFactory&)> onMockCreate;
};

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEVICEINFOHANDLERFACTORY_CLASS_H
