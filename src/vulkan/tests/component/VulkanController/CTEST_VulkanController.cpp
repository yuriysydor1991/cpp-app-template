#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <vulkan/vulkan.h>

#include "src/app/ApplicationContext.h"
#include "src/vulkan/VulkanController.h"

using namespace testing;
using namespace vulkani;

class CTEST_VulkanController : public Test
{
 public:
  CTEST_VulkanController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
  }

  /**
   * @brief Whether a Vulkan instance can be created in this environment.
   *
   * Mirrors what the controller's init() does, but with a throwaway probe
   * instance, so the test can branch on the runtime availability without
   * coupling to the controller under test.
   */
  static bool vulkan_instance_creatable()
  {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance probe = VK_NULL_HANDLE;

    if (vkCreateInstance(&createInfo, nullptr, &probe) != VK_SUCCESS) {
      return false;
    }

    vkDestroyInstance(probe, nullptr);

    return true;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx;
};

TEST_F(CTEST_VulkanController, create_reflects_runtime_availability)
{
  VulkanControllerPtr controller = VulkanController::create();

  if (vulkan_instance_creatable()) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() reports the failure by returning false, so create() hands back an
    // empty pointer instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}

TEST_F(CTEST_VulkanController, run_against_live_runtime)
{
  if (!vulkan_instance_creatable()) {
    GTEST_SKIP() << "No usable Vulkan runtime is available in this environment";
  }

  VulkanControllerPtr controller = VulkanController::create();

  ASSERT_NE(controller, nullptr);

  // With a usable Vulkan loader the demo enumerates the physical devices (zero
  // is a valid, successful outcome) and must complete successfully.
  EXPECT_TRUE(controller->run(appCtx));
}
