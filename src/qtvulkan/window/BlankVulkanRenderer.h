#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANRENDERER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANRENDERER_CLASS_H

#include <QVulkanWindow>

namespace qtvulkani
{

/**
 * @brief A minimal QVulkanWindowRenderer that clears every frame to opaque
 * black.
 *
 * It begins the QVulkanWindow default render pass with a black clear color and
 * ends it right away, recording no draw commands. The result is a blank, black
 * window rendered through Vulkan - the native Qt Vulkan counterpart of the
 * blank windows shown by the appSDL2 / appFreeGlut branches. The actual Vulkan
 * draw commands are meant to be recorded between the render pass begin and end
 * calls to build a real scene.
 */
class BlankVulkanRenderer : public QVulkanWindowRenderer
{
 public:
  /**
   * @brief Constructs the renderer bound to the given window.
   *
   * @param gwindow The owning QVulkanWindow the renderer draws into. Must not
   * be a nullptr and must outlive the renderer (the QVulkanWindow owns and
   * destroys its renderer).
   */
  explicit BlankVulkanRenderer(QVulkanWindow* gwindow);

  /**
   * @brief Records and submits a single frame that just clears to black.
   */
  void startNextFrame() override;

 private:
  QVulkanWindow* window;
};

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BLANKVULKANRENDERER_CLASS_H
