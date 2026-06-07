#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QTVULKANCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QTVULKANCONTROLLER_CLASS_H

#include <memory>
#include <optional>

#include <QVulkanInstance>

/**
 * @brief The namespace to contain all the entities related to the native Qt
 * Vulkan (QVulkanInstance) based device information component.
 */
namespace qtvulkani
{

/**
 * @brief Owns the QVulkanInstance and drives the physical device enumeration
 * through a device info handler.
 *
 * The native Qt Vulkan (Qt6::Gui QVulkanInstance) counterpart of the app-based
 * appVulkan branch VulkanController. Created through the static create() factory
 * method which brings up the Vulkan instance up front, so a non-null instance is
 * always usable. A living QGuiApplication is required by the platform Vulkan
 * integration before create() is called.
 */
class QtVulkanController
{
 public:
  using QtVulkanControllerPtr = std::shared_ptr<QtVulkanController>;

  virtual ~QtVulkanController() = default;
  QtVulkanController() = default;

  /**
   * @brief Enumerates the Vulkan physical devices and logs their properties.
   *
   * @return Returns true on success and false if the controller is not
   * initialized or the device info handler reports a failure.
   */
  virtual bool run();

  /**
   * @brief Creates a controller with an already created Vulkan instance.
   *
   * @return Returns the created controller, or an empty pointer when no usable
   * Vulkan instance can be created in the current environment (no driver, or a
   * platform plugin without Vulkan support).
   */
  static QtVulkanControllerPtr create();

  /**
   * @brief Provides the created Vulkan instance owned by the controller.
   *
   * Lets the GUI reuse the very same instance the controller brought up and
   * validated (a QVulkanInstance is designed to be shared, e.g. assigned to a
   * QVulkanWindow with setVulkanInstance()). The returned pointer stays valid
   * for as long as the controller is alive.
   *
   * @return A pointer to the held QVulkanInstance, or nullptr when none is held.
   */
  QVulkanInstance* vulkan_instance();

 protected:
  virtual bool init();
  virtual bool inited() const;

  /**
   * @brief The instance handed down to the device info handlers.
   *
   * Exposed as an overridable seam so the orchestration in run() may be unit
   * tested without a live Vulkan runtime.
   *
   * @return A pointer to the held QVulkanInstance, or nullptr when none is held.
   */
  virtual QVulkanInstance* instance_ptr();

  std::optional<QVulkanInstance> vulkanInstance;

 private:
  bool make_device_info_call();
};

using QtVulkanControllerPtr = QtVulkanController::QtVulkanControllerPtr;

}  // namespace qtvulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QTVULKANCONTROLLER_CLASS_H
