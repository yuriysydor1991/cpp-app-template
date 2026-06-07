#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANWINDOW_CLASS_H

#include <QVulkanWindow>

namespace qtvulkani
{

/**
 * @brief A QVulkanWindow that displays a blank, black, Vulkan rendered surface.
 *
 * QVulkanWindow takes care of the surface, the swap chain, the logical device
 * and the per frame command buffers; this subclass only hands it a
 * BlankVulkanRenderer through createRenderer(). A living QVulkanInstance has to
 * be assigned with setVulkanInstance() before the window is shown.
 */
class BlankVulkanWindow : public QVulkanWindow
{
 public:
  /**
   * @brief Creates the renderer driving this window.
   *
   * Called by QVulkanWindow once the window is exposed. The returned renderer is
   * owned (and destroyed) by the QVulkanWindow.
   *
   * @return Returns a newly created BlankVulkanRenderer bound to this window.
   */
  QVulkanWindowRenderer* createRenderer() override;
};

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANWINDOW_CLASS_H
