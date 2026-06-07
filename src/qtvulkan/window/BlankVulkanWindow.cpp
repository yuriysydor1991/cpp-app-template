#include "src/qtvulkan/window/BlankVulkanWindow.h"

#include "src/qtvulkan/window/BlankVulkanRenderer.h"

namespace qtvulkani
{

QVulkanWindowRenderer* BlankVulkanWindow::createRenderer()
{
  // Ownership of the renderer is transferred to the QVulkanWindow, which
  // destroys it together with the window.
  return new BlankVulkanRenderer(this);
}

}  // namespace qtvulkani
