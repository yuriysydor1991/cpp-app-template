#include "src/vulkan/VulkanController.h"

#include <cassert>
#include <memory>

#include <vulkan/vulkan.h>

#include "src/log/log.h"
#include "src/vulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/vulkan/device-info/IDeviceInfoHandler.h"

namespace vulkani
{

VulkanController::~VulkanController()
{
  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
  }
}

bool VulkanController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return false;
  }

  appctx = ctx;

  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  if (!enumerate_physical_devices()) {
    LOGE("Physical device enumeration failure");
    return false;
  }

  return true;
}

bool VulkanController::init()
{
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = applicationName;
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = engineName;
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = apiVersion;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledLayerCount = 0;
  createInfo.ppEnabledLayerNames = nullptr;
  createInfo.enabledExtensionCount = 0;
  createInfo.ppEnabledExtensionNames = nullptr;

  const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

  if (result != VK_SUCCESS) {
    LOGE("vkCreateInstance failed with the VkResult code: "
         << static_cast<int>(result));
    instance = VK_NULL_HANDLE;
    return false;
  }

  assert(instance != VK_NULL_HANDLE);

  LOGD("Vulkan instance created");

  return true;
}

bool VulkanController::inited() { return instance != VK_NULL_HANDLE; }

bool VulkanController::enumerate_physical_devices()
{
  assert(instance != VK_NULL_HANDLE);

  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  DeviceInfoHandlerFactory factory;

  IDeviceInfoHandlerPtr handler = factory.create_default_handler();

  assert(handler != nullptr);

  if (handler == nullptr) {
    LOGE("Fail to create a device info handler");
    return false;
  }

  return handler->handle(instance);
}

VulkanControllerPtr VulkanController::create()
{
  VulkanControllerPtr ptr = std::make_shared<VulkanController>();

  if (!ptr->init()) {
    LOGE("Fail to init the newly created controller");
    return {};
  }

  return ptr;
}

}  // namespace vulkani
