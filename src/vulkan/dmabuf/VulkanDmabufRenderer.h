#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANDMABUFRENDERER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANDMABUFRENDERER_CLASS_H

#include <cstdint>
#include <memory>
#include <optional>

#include <vulkan/vulkan.h>

#include "src/vulkan/dmabuf/DmabufFrame.h"

namespace vulkani
{

/**
 * @brief Renders a single cleared frame into an off-screen Vulkan image and
 * exports it as a Linux dma-buf, so the GTK side can display genuine Vulkan
 * output in a Gtk::Picture (GTK4 exposes no Vulkan rendering widget).
 *
 * The pipeline is: create an instance + logical device that support the
 * external-memory / dma-buf / DRM-format-modifier extensions, create a
 * DRM-format-modifier (linear) color image backed by exportable memory, clear
 * it through a render pass, wait for completion, then export the memory as a
 * dma-buf file descriptor (vkGetMemoryFdKHR). The renderer owns all the Vulkan
 * objects and the file descriptor and keeps them alive until destruction, so
 * the produced Gdk texture stays valid.
 *
 * create() returns an empty pointer when the required extensions are not
 * available in the current environment (e.g. a software ICD such as lavapipe,
 * or no Vulkan device at all), which lets the caller fall back gracefully.
 */
class VulkanDmabufRenderer
{
 public:
  using VulkanDmabufRendererPtr = std::unique_ptr<VulkanDmabufRenderer>;

  VulkanDmabufRenderer() = default;
  ~VulkanDmabufRenderer();

  VulkanDmabufRenderer(const VulkanDmabufRenderer&) = delete;
  VulkanDmabufRenderer& operator=(const VulkanDmabufRenderer&) = delete;
  VulkanDmabufRenderer(VulkanDmabufRenderer&&) = delete;
  VulkanDmabufRenderer& operator=(VulkanDmabufRenderer&&) = delete;

  /**
   * @brief Creates a renderer that has already produced one cleared frame.
   *
   * @param width The image width in pixels.
   * @param height The image height in pixels.
   * @param r,g,b,a The normalized [0;1] clear color components.
   *
   * @return The ready renderer holding an exported dma-buf, or an empty pointer
   * when the dma-buf rendering path is not available in this environment.
   */
  static VulkanDmabufRendererPtr create(std::uint32_t width,
                                        std::uint32_t height, float r, float g,
                                        float b, float a);

  /**
   * @brief The exported dma-buf description, valid only on a ready renderer.
   */
  const std::optional<DmabufFrame>& frame() const { return frameInfo; }

 private:
  bool init(std::uint32_t width, std::uint32_t height, float r, float g,
            float b, float a);

  bool create_instance();
  bool select_physical_device();
  bool create_logical_device();
  bool create_image(std::uint32_t width, std::uint32_t height);
  bool allocate_memory();
  bool create_render_target(std::uint32_t width, std::uint32_t height);
  bool render(std::uint32_t width, std::uint32_t height, float r, float g,
              float b, float a);
  bool export_dmabuf(std::uint32_t width, std::uint32_t height);

  std::uint32_t find_memory_type(std::uint32_t typeBits,
                                 VkMemoryPropertyFlags want) const;

  void cleanup();

  VkInstance instance{VK_NULL_HANDLE};
  VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
  std::uint32_t queueFamily{0};
  VkDevice device{VK_NULL_HANDLE};
  VkQueue queue{VK_NULL_HANDLE};
  VkImage image{VK_NULL_HANDLE};
  VkDeviceMemory memory{VK_NULL_HANDLE};
  VkImageView imageView{VK_NULL_HANDLE};
  VkRenderPass renderPass{VK_NULL_HANDLE};
  VkFramebuffer framebuffer{VK_NULL_HANDLE};
  VkCommandPool commandPool{VK_NULL_HANDLE};

  PFN_vkGetMemoryFdKHR pfnGetMemoryFdKHR{nullptr};
  PFN_vkGetImageDrmFormatModifierPropertiesEXT pfnGetModifierProperties{nullptr};

  std::optional<DmabufFrame> frameInfo;
};

using VulkanDmabufRendererPtr = VulkanDmabufRenderer::VulkanDmabufRendererPtr;

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANDMABUFRENDERER_CLASS_H
