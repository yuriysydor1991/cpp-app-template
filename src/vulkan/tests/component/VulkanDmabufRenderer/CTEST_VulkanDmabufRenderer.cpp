#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vulkan/vulkan.h>

#include <cstdint>

#include "src/vulkan/VulkanController.h"
#include "src/vulkan/dmabuf/DmabufFrame.h"
#include "src/vulkan/dmabuf/VulkanDmabufRenderer.h"

using namespace testing;
using namespace vulkani;

/**
 * @brief Covers the dma-buf renderer against the real Vulkan runtime: either
 * a cleared frame is exported, or the documented empty pointer fallback is
 * returned on an environment without the dma-buf export support.
 */
class CTEST_VulkanDmabufRenderer : public Test
{
 public:
  inline static constexpr std::uint32_t width = 64;
  inline static constexpr std::uint32_t height = 32;
};

TEST_F(CTEST_VulkanDmabufRenderer, missing_instance_is_rejected)
{
  EXPECT_EQ(VulkanDmabufRenderer::create(VK_NULL_HANDLE, width, height, 0.0F,
                                         0.0F, 0.0F, 1.0F),
            nullptr);
}

TEST_F(CTEST_VulkanDmabufRenderer, frame_is_exported_or_cleanly_refused)
{
  VulkanControllerPtr controller = VulkanController::create();

  if (controller == nullptr) {
    GTEST_SKIP() << "No Vulkan runtime is available in this environment";
  }

  auto renderer = VulkanDmabufRenderer::create(
      controller->vulkan_instance(), width, height, 0.0F, 0.0F, 0.0F, 1.0F);

  if (renderer == nullptr) {
    GTEST_SKIP() << "No Vulkan device exports dma-bufs in this environment";
  }

  ASSERT_TRUE(renderer->frame().has_value());

  const DmabufFrame& frame = renderer->frame().value();

  EXPECT_GE(frame.fd, 0);
  EXPECT_EQ(frame.width, width);
  EXPECT_EQ(frame.height, height);
  EXPECT_GE(frame.stride, width * 4U);
}
