#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H

#include <vulkan/vulkan.h>

#include <cstdint>
#include <memory>

/**
 * @brief The namespace to contain all the entities related to the Vulkan API
 * usage demonstration component.
 */
namespace vulkani
{

/**
 * @brief Owns the single Vulkan instance of the application and drives the
 * demonstration work (the physical device enumeration and logging).
 *
 * The controller is created through the static create() factory which brings up
 * a VkInstance up front, so a non-null controller is always usable. The unit
 * tests replace the Vulkan loader with the header-only vulkan.h mock, the real
 * path is exercised by the component test against the system Vulkan runtime.
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

  /// @brief The Vulkan API version the instance is created against: 1.2, since
  /// the dma-buf renderer shares the instance and needs the 1.1+ queries.
  inline static constexpr std::uint32_t apiVersion = VK_API_VERSION_1_2;

  virtual ~VulkanController();
  VulkanController() = default;

  VulkanController(const VulkanController&) = delete;
  VulkanController& operator=(const VulkanController&) = delete;

  /**
   * @brief Runs the demonstration work against the already created instance.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool run();

  /**
   * @brief Creates a ready to use controller with an already created Vulkan
   * instance.
   *
   * @return Returns the created controller or an empty pointer in case the
   * Vulkan instance could not be created (no usable loader / driver).
   */
  static VulkanControllerPtr create();

  /**
   * @brief Provides the instance owned by the controller, so the other Vulkan
   * users (the dma-buf renderer) share it instead of creating their own.
   *
   * @return The created instance, valid for as long as the controller lives.
   */
  VkInstance vulkan_instance() const;

 private:
  bool init();
  bool inited() const;
  bool enumerate_physical_devices();

  VkInstance instance{VK_NULL_HANDLE};
};

using VulkanControllerPtr = VulkanController::VulkanControllerPtr;

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_VULKANCONTROLLER_CLASS_H
