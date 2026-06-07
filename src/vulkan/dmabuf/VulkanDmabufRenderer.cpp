#include "src/vulkan/dmabuf/VulkanDmabufRenderer.h"

#include <unistd.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#include <vulkan/vulkan.h>

#include "src/log/log.h"

namespace vulkani
{

namespace
{

/// @brief Builds a DRM fourcc code without the C-cast macros from drm_fourcc.h.
constexpr std::uint32_t drm_fourcc(char a, char b, char c, char d)
{
  return static_cast<std::uint32_t>(static_cast<unsigned char>(a)) |
         (static_cast<std::uint32_t>(static_cast<unsigned char>(b)) << 8) |
         (static_cast<std::uint32_t>(static_cast<unsigned char>(c)) << 16) |
         (static_cast<std::uint32_t>(static_cast<unsigned char>(d)) << 24);
}

// 32 bpp, opaque (alpha ignored), matching VK_FORMAT_B8G8R8A8_UNORM in memory.
constexpr std::uint32_t DRM_FORMAT_XRGB8888 = drm_fourcc('X', 'R', '2', '4');
constexpr std::uint64_t DRM_FORMAT_MODIFIER_LINEAR = 0;

constexpr VkFormat IMAGE_FORMAT = VK_FORMAT_B8G8R8A8_UNORM;

// VK_EXT_image_drm_format_modifier (and its dependencies) is core-complete on a
// Vulkan 1.2 device, so the renderer targets 1.2 and only has to enable the
// dma-buf related device extensions explicitly.
const std::array<const char*, 3> kRequiredDeviceExtensions{
    VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,
    VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME,
    VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,
};

bool device_supports_required_extensions(VkPhysicalDevice candidate)
{
  std::uint32_t count = 0;
  vkEnumerateDeviceExtensionProperties(candidate, nullptr, &count, nullptr);

  std::vector<VkExtensionProperties> available(count);
  vkEnumerateDeviceExtensionProperties(candidate, nullptr, &count,
                                       available.data());

  for (const char* required : kRequiredDeviceExtensions) {
    bool found = false;
    for (const VkExtensionProperties& props : available) {
      if (std::strcmp(props.extensionName, required) == 0) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }

  return true;
}

}  // namespace

VulkanDmabufRenderer::~VulkanDmabufRenderer() { cleanup(); }

VulkanDmabufRenderer::VulkanDmabufRendererPtr VulkanDmabufRenderer::create(
    std::uint32_t width, std::uint32_t height, float r, float g, float b,
    float a)
{
  auto renderer =
      std::unique_ptr<VulkanDmabufRenderer>(new VulkanDmabufRenderer());

  if (!renderer->init(width, height, r, g, b, a)) {
    return nullptr;
  }

  return renderer;
}

bool VulkanDmabufRenderer::init(std::uint32_t width, std::uint32_t height,
                                float r, float g, float b, float a)
{
  return create_instance() && select_physical_device() &&
         create_logical_device() && create_image(width, height) &&
         allocate_memory() && create_render_target(width, height) &&
         render(width, height, r, g, b, a) && export_dmabuf(width, height);
}

bool VulkanDmabufRenderer::create_instance()
{
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "cpp-app-template-gtkmm4-vulkan";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "cpp-app-template";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_2;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

  if (result != VK_SUCCESS) {
    LOGE("vkCreateInstance failed with the VkResult code: "
         << static_cast<int>(result));
    instance = VK_NULL_HANDLE;
    return false;
  }

  return true;
}

bool VulkanDmabufRenderer::select_physical_device()
{
  std::uint32_t count = 0;
  vkEnumeratePhysicalDevices(instance, &count, nullptr);

  if (count == 0) {
    LOGE("No Vulkan physical devices available");
    return false;
  }

  std::vector<VkPhysicalDevice> devices(count, VK_NULL_HANDLE);
  vkEnumeratePhysicalDevices(instance, &count, devices.data());

  for (const VkPhysicalDevice candidate : devices) {
    if (!device_supports_required_extensions(candidate)) {
      continue;
    }

    std::uint32_t familyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(candidate, &familyCount, nullptr);

    std::vector<VkQueueFamilyProperties> families(familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(candidate, &familyCount,
                                             families.data());

    for (std::uint32_t i = 0; i < familyCount; ++i) {
      if ((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0U) {
        physicalDevice = candidate;
        queueFamily = i;
        return true;
      }
    }
  }

  LOGE(
      "No Vulkan device exposes the dma-buf / DRM format modifier extensions "
      "required to render into a GTK surface");
  return false;
}

bool VulkanDmabufRenderer::create_logical_device()
{
  const float priority = 1.0F;

  VkDeviceQueueCreateInfo queueInfo{};
  queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueInfo.queueFamilyIndex = queueFamily;
  queueInfo.queueCount = 1;
  queueInfo.pQueuePriorities = &priority;

  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.queueCreateInfoCount = 1;
  createInfo.pQueueCreateInfos = &queueInfo;
  createInfo.enabledExtensionCount =
      static_cast<std::uint32_t>(kRequiredDeviceExtensions.size());
  createInfo.ppEnabledExtensionNames = kRequiredDeviceExtensions.data();

  const VkResult result =
      vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);

  if (result != VK_SUCCESS) {
    LOGE("vkCreateDevice failed with the VkResult code: "
         << static_cast<int>(result));
    device = VK_NULL_HANDLE;
    return false;
  }

  vkGetDeviceQueue(device, queueFamily, 0, &queue);

  pfnGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(
      vkGetDeviceProcAddr(device, "vkGetMemoryFdKHR"));
  pfnGetModifierProperties =
      reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(
          vkGetDeviceProcAddr(device,
                              "vkGetImageDrmFormatModifierPropertiesEXT"));

  if (pfnGetMemoryFdKHR == nullptr || pfnGetModifierProperties == nullptr) {
    LOGE("Failed to resolve the dma-buf export entry points");
    return false;
  }

  return true;
}

bool VulkanDmabufRenderer::create_image(std::uint32_t width,
                                        std::uint32_t height)
{
  std::array<std::uint64_t, 1> modifiers{DRM_FORMAT_MODIFIER_LINEAR};

  VkImageDrmFormatModifierListCreateInfoEXT modifierList{};
  modifierList.sType =
      VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT;
  modifierList.drmFormatModifierCount =
      static_cast<std::uint32_t>(modifiers.size());
  modifierList.pDrmFormatModifiers = modifiers.data();

  VkExternalMemoryImageCreateInfo externalInfo{};
  externalInfo.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
  externalInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT;
  externalInfo.pNext = &modifierList;

  VkImageCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  createInfo.pNext = &externalInfo;
  createInfo.imageType = VK_IMAGE_TYPE_2D;
  createInfo.format = IMAGE_FORMAT;
  createInfo.extent = VkExtent3D{width, height, 1U};
  createInfo.mipLevels = 1;
  createInfo.arrayLayers = 1;
  createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  createInfo.tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;
  createInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

  const VkResult result =
      vkCreateImage(device, &createInfo, nullptr, &image);

  if (result != VK_SUCCESS) {
    LOGE("vkCreateImage (DRM format modifier) failed with the VkResult code: "
         << static_cast<int>(result));
    image = VK_NULL_HANDLE;
    return false;
  }

  return true;
}

std::uint32_t VulkanDmabufRenderer::find_memory_type(
    std::uint32_t typeBits, VkMemoryPropertyFlags want) const
{
  VkPhysicalDeviceMemoryProperties memProps{};
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);

  for (std::uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
    const bool typeAllowed = (typeBits & (1U << i)) != 0U;
    const bool hasProps =
        (memProps.memoryTypes[i].propertyFlags & want) == want;
    if (typeAllowed && hasProps) {
      return i;
    }
  }

  // Fall back to any allowed memory type when the preferred flags are absent.
  for (std::uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
    if ((typeBits & (1U << i)) != 0U) {
      return i;
    }
  }

  return std::numeric_limits<std::uint32_t>::max();
}

bool VulkanDmabufRenderer::allocate_memory()
{
  VkMemoryRequirements requirements{};
  vkGetImageMemoryRequirements(device, image, &requirements);

  const std::uint32_t memoryType = find_memory_type(
      requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  if (memoryType == std::numeric_limits<std::uint32_t>::max()) {
    LOGE("No suitable Vulkan memory type for the exportable image");
    return false;
  }

  // Dedicated allocation is recommended (and often required) for exported
  // images.
  VkMemoryDedicatedAllocateInfo dedicated{};
  dedicated.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
  dedicated.image = image;

  VkExportMemoryAllocateInfo exportInfo{};
  exportInfo.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
  exportInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT;
  exportInfo.pNext = &dedicated;

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.pNext = &exportInfo;
  allocInfo.allocationSize = requirements.size;
  allocInfo.memoryTypeIndex = memoryType;

  if (vkAllocateMemory(device, &allocInfo, nullptr, &memory) != VK_SUCCESS) {
    LOGE("vkAllocateMemory for the exportable image failed");
    memory = VK_NULL_HANDLE;
    return false;
  }

  if (vkBindImageMemory(device, image, memory, 0) != VK_SUCCESS) {
    LOGE("vkBindImageMemory for the exportable image failed");
    return false;
  }

  return true;
}

bool VulkanDmabufRenderer::create_render_target(std::uint32_t width,
                                                std::uint32_t height)
{
  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = IMAGE_FORMAT;
  viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
    LOGE("vkCreateImageView failed");
    imageView = VK_NULL_HANDLE;
    return false;
  }

  VkAttachmentDescription color{};
  color.format = IMAGE_FORMAT;
  color.samples = VK_SAMPLE_COUNT_1_BIT;
  color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  // GENERAL is a layout an external (EGL / dma-buf) consumer can sample from.
  color.finalLayout = VK_IMAGE_LAYOUT_GENERAL;

  VkAttachmentReference colorRef{};
  colorRef.attachment = 0;
  colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorRef;

  // Make the color writes available to the external consumer after the pass.
  VkSubpassDependency dependency{};
  dependency.srcSubpass = 0;
  dependency.dstSubpass = VK_SUBPASS_EXTERNAL;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
  dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  dependency.dstAccessMask = 0;

  VkRenderPassCreateInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = 1;
  renderPassInfo.pAttachments = &color;
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;
  renderPassInfo.dependencyCount = 1;
  renderPassInfo.pDependencies = &dependency;

  if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) !=
      VK_SUCCESS) {
    LOGE("vkCreateRenderPass failed");
    renderPass = VK_NULL_HANDLE;
    return false;
  }

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderPass;
  framebufferInfo.attachmentCount = 1;
  framebufferInfo.pAttachments = &imageView;
  framebufferInfo.width = width;
  framebufferInfo.height = height;
  framebufferInfo.layers = 1;

  if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer) !=
      VK_SUCCESS) {
    LOGE("vkCreateFramebuffer failed");
    framebuffer = VK_NULL_HANDLE;
    return false;
  }

  return true;
}

bool VulkanDmabufRenderer::render(std::uint32_t width, std::uint32_t height,
                                  float r, float g, float b, float a)
{
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
  poolInfo.queueFamilyIndex = queueFamily;

  if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) !=
      VK_SUCCESS) {
    LOGE("vkCreateCommandPool failed");
    commandPool = VK_NULL_HANDLE;
    return false;
  }

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
  if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) !=
      VK_SUCCESS) {
    LOGE("vkAllocateCommandBuffers failed");
    return false;
  }

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  vkBeginCommandBuffer(commandBuffer, &beginInfo);

  VkClearValue clearValue{};
  clearValue.color.float32[0] = r;
  clearValue.color.float32[1] = g;
  clearValue.color.float32[2] = b;
  clearValue.color.float32[3] = a;

  VkRenderPassBeginInfo passBegin{};
  passBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  passBegin.renderPass = renderPass;
  passBegin.framebuffer = framebuffer;
  passBegin.renderArea.offset = VkOffset2D{0, 0};
  passBegin.renderArea.extent = VkExtent2D{width, height};
  passBegin.clearValueCount = 1;
  passBegin.pClearValues = &clearValue;

  // No draw commands: the render pass clears the image to the requested color.
  vkCmdBeginRenderPass(commandBuffer, &passBegin, VK_SUBPASS_CONTENTS_INLINE);
  vkCmdEndRenderPass(commandBuffer);

  vkEndCommandBuffer(commandBuffer);

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  VkFence fence = VK_NULL_HANDLE;
  if (vkCreateFence(device, &fenceInfo, nullptr, &fence) != VK_SUCCESS) {
    LOGE("vkCreateFence failed");
    return false;
  }

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  bool ok = vkQueueSubmit(queue, 1, &submitInfo, fence) == VK_SUCCESS;

  if (ok) {
    ok = vkWaitForFences(device, 1, &fence, VK_TRUE,
                         std::numeric_limits<std::uint64_t>::max()) ==
         VK_SUCCESS;
  }

  vkDestroyFence(device, fence, nullptr);

  if (!ok) {
    LOGE("Submitting / waiting for the clear command buffer failed");
    return false;
  }

  return true;
}

bool VulkanDmabufRenderer::export_dmabuf(std::uint32_t width,
                                         std::uint32_t height)
{
  VkImageDrmFormatModifierPropertiesEXT modifierProps{};
  modifierProps.sType =
      VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT;

  if (pfnGetModifierProperties(device, image, &modifierProps) != VK_SUCCESS) {
    LOGE("vkGetImageDrmFormatModifierPropertiesEXT failed");
    return false;
  }

  VkImageSubresource subresource{};
  subresource.aspectMask = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
  subresource.mipLevel = 0;
  subresource.arrayLayer = 0;

  VkSubresourceLayout layout{};
  vkGetImageSubresourceLayout(device, image, &subresource, &layout);

  VkMemoryGetFdInfoKHR getFdInfo{};
  getFdInfo.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
  getFdInfo.memory = memory;
  getFdInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT;

  int fd = -1;
  if (pfnGetMemoryFdKHR(device, &getFdInfo, &fd) != VK_SUCCESS || fd < 0) {
    LOGE("vkGetMemoryFdKHR failed to export the dma-buf");
    return false;
  }

  DmabufFrame result;
  result.fd = fd;
  result.width = width;
  result.height = height;
  result.stride = static_cast<std::uint32_t>(layout.rowPitch);
  result.offset = static_cast<std::uint32_t>(layout.offset);
  result.fourcc = DRM_FORMAT_XRGB8888;
  result.modifier = modifierProps.drmFormatModifier;

  frameInfo = result;

  LOGD("Exported a "
       << width << "x" << height
       << " Vulkan dma-buf (stride=" << result.stride
       << ", modifier=" << result.modifier << ")");

  return true;
}

void VulkanDmabufRenderer::cleanup()
{
  if (device != VK_NULL_HANDLE) {
    vkDeviceWaitIdle(device);

    if (framebuffer != VK_NULL_HANDLE) {
      vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
    if (renderPass != VK_NULL_HANDLE) {
      vkDestroyRenderPass(device, renderPass, nullptr);
    }
    if (imageView != VK_NULL_HANDLE) {
      vkDestroyImageView(device, imageView, nullptr);
    }
    if (commandPool != VK_NULL_HANDLE) {
      vkDestroyCommandPool(device, commandPool, nullptr);
    }
    if (image != VK_NULL_HANDLE) {
      vkDestroyImage(device, image, nullptr);
    }
    if (memory != VK_NULL_HANDLE) {
      vkFreeMemory(device, memory, nullptr);
    }

    vkDestroyDevice(device, nullptr);
    device = VK_NULL_HANDLE;
  }

  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
  }

  if (frameInfo.has_value() && frameInfo->fd >= 0) {
    close(frameInfo->fd);
    frameInfo->fd = -1;
  }
}

}  // namespace vulkani
