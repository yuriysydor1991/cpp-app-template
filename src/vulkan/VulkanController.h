#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H

#include <cstdint>
#include <memory>

#include <vulkan/vulkan.h>

#include "src/app/ApplicationContext.h"

/**
 * @brief The namespace to contain all the entities related to the Vulkan API
 * usage demonstration component.
 */
namespace vulkani
{

/**
 * @brief Owns the Vulkan instance life cycle and drives the demonstration
 * work (the physical device enumeration and logging).
 *
 * The controller is created through the static create() factory which brings up
 * a VkInstance up front, so a non-null controller is always usable. The actual
 * Vulkan touching steps (the instance creation and the @ref inited() check) are
 * kept behind small protected, overridable seams, so the run() orchestration
 * may be unit tested without a live Vulkan loader. The real path is exercised by
 * the component test against the system Vulkan runtime.
 */
class VulkanController
{
 public:
  using VulkanControllerPtr = std::shared_ptr<VulkanController>;

  /// @brief The application name reported to the Vulkan loader at instance
  /// creation time.
  inline static constexpr const char* const applicationName =
      "cpp-app-template-vulkan-app";

  /// @brief The engine name reported to the Vulkan loader at instance creation
  /// time.
  inline static constexpr const char* const engineName =
      "cpp-app-template-vulkan-engine";

  /// @brief The Vulkan API version the instance is created against.
  inline static constexpr std::uint32_t apiVersion = VK_API_VERSION_1_0;

  virtual ~VulkanController();
  VulkanController() = default;

  /**
   * @brief Runs the demonstration work against the already created instance.
   *
   * @param ctx Application's run context. Must not be a nullptr.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  /**
   * @brief Creates a ready to use controller with an already created Vulkan
   * instance.
   *
   * @return Returns the created controller or an empty pointer in case the
   * Vulkan instance could not be created (no usable loader / driver).
   */
  static VulkanControllerPtr create();

 protected:
  /**
   * @brief Creates the VkInstance. The only instance-creating seam, overridable
   * for the unit tests.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool init();

  /**
   * @brief Reports whether a usable Vulkan instance has been created.
   *
   * @return Returns true when the instance is valid and false otherwise.
   */
  virtual bool inited();

  std::shared_ptr<app::ApplicationContext> appctx;

 private:
  bool enumerate_physical_devices();

  VkInstance instance{VK_NULL_HANDLE};
};

using VulkanControllerPtr = VulkanController::VulkanControllerPtr;

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H
