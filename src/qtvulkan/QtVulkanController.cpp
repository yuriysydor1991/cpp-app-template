#include "src/qtvulkan/QtVulkanController.h"

#include <memory>

#include <QVersionNumber>
#include <QVulkanInstance>

#include "src/log/log.h"
#include "src/qtvulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"

namespace qtvulkani
{

bool QtVulkanController::run()
{
  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  return make_device_info_call();
}

bool QtVulkanController::init()
{
  // Request a Vulkan 1.0 instance. create() returns false (without throwing)
  // when no usable driver is present or when the active Qt platform plugin does
  // not support Vulkan, in which case the controller stays uninitialized.
  vulkanInstance.emplace();
  vulkanInstance->setApiVersion(QVersionNumber(1, 0, 0));

  if (!vulkanInstance->create()) {
    LOGE("Fail to create the QVulkanInstance, error code: "
         << vulkanInstance->errorCode());
    vulkanInstance.reset();
    return false;
  }

  LOGD("QVulkanInstance created");

  return true;
}

bool QtVulkanController::inited() const
{
  return vulkanInstance.has_value() && vulkanInstance->isValid();
}

QVulkanInstance* QtVulkanController::instance_ptr()
{
  return vulkanInstance.has_value() ? &vulkanInstance.value() : nullptr;
}

QVulkanInstance* QtVulkanController::vulkan_instance()
{
  return instance_ptr();
}

bool QtVulkanController::make_device_info_call()
{
  DeviceInfoHandlerFactory factory;

  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  if (handler == nullptr) {
    LOGE("Fail to create a device info handler");
    return false;
  }

  return handler->handle(instance_ptr());
}

QtVulkanControllerPtr QtVulkanController::create()
{
  QtVulkanControllerPtr ptr = std::make_shared<QtVulkanController>();

  if (!ptr->init()) {
    LOGE("Fail to init the newly created controller");
    return {};
  }

  return ptr;
}

}  // namespace qtvulkani
