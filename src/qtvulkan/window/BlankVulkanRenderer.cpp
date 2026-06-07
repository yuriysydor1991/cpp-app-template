#include "src/qtvulkan/window/BlankVulkanRenderer.h"

#include <array>
#include <cstdint>

#include <QSize>
#include <QVulkanDeviceFunctions>
#include <QVulkanInstance>
#include <vulkan/vulkan.h>

namespace qtvulkani
{

BlankVulkanRenderer::BlankVulkanRenderer(QVulkanWindow* gwindow)
    : window{gwindow}
{
}

void BlankVulkanRenderer::startNextFrame()
{
  const QSize imageSize = window->swapChainImageSize();

  VkClearColorValue clearColor{};
  clearColor.float32[0] = 0.0F;
  clearColor.float32[1] = 0.0F;
  clearColor.float32[2] = 0.0F;
  clearColor.float32[3] = 1.0F;

  VkClearDepthStencilValue clearDepthStencil{};
  clearDepthStencil.depth = 1.0F;
  clearDepthStencil.stencil = 0U;

  // The QVulkanWindow default render pass has two attachments (the color one
  // and the depth / stencil one), so two matching clear values are provided.
  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = clearColor;
  clearValues[1].depthStencil = clearDepthStencil;

  VkRenderPassBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  beginInfo.renderPass = window->defaultRenderPass();
  beginInfo.framebuffer = window->currentFramebuffer();
  beginInfo.renderArea.extent.width =
      static_cast<std::uint32_t>(imageSize.width());
  beginInfo.renderArea.extent.height =
      static_cast<std::uint32_t>(imageSize.height());
  beginInfo.clearValueCount = static_cast<std::uint32_t>(clearValues.size());
  beginInfo.pClearValues = clearValues.data();

  VkCommandBuffer commandBuffer = window->currentCommandBuffer();
  QVulkanDeviceFunctions* deviceFunctions =
      window->vulkanInstance()->deviceFunctions(window->device());

  deviceFunctions->vkCmdBeginRenderPass(commandBuffer, &beginInfo,
                                        VK_SUBPASS_CONTENTS_INLINE);
  // No draw commands are recorded, so the render pass simply clears the frame
  // buffer to black. Record the Vulkan draw commands here to render a scene.
  deviceFunctions->vkCmdEndRenderPass(commandBuffer);

  window->frameReady();
}

}  // namespace qtvulkani
