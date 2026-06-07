#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include <vulkan/vulkan.h>

#include "src/app/ApplicationContext.h"
#include "src/vulkan/VulkanController.h"
#include "src/vulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/vulkan/device-info/IDeviceInfoHandler.h"

using namespace testing;
using namespace vulkani;

class UTEST_VulkanController : public Test
{
 public:
  UTEST_VulkanController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)},
        handler{std::make_shared<NiceMock<IDeviceInfoHandler>>()}
  {
    // The controller builds a DeviceInfoHandlerFactory internally; route every
    // created factory to hand out the fixture's mock handler.
    DeviceInfoHandlerFactory::onMockCreate = [this](
                                                 DeviceInfoHandlerFactory& f) {
      EXPECT_CALL(f, create_default_handler()).WillRepeatedly(Return(handler));
    };
    vkmock::fail_instance_creation() = false;
  }

  ~UTEST_VulkanController() override
  {
    DeviceInfoHandlerFactory::onMockCreate = nullptr;
    vkmock::fail_instance_creation() = false;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx;
  std::shared_ptr<NiceMock<IDeviceInfoHandler>> handler;
};

TEST_F(UTEST_VulkanController, run_returns_false_on_null_context)
{
  VulkanController controller;

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // nullptr guard inside run() is what is being exercised here.
  EXPECT_FALSE(controller.run(nullptr));
}

TEST_F(UTEST_VulkanController, run_returns_false_when_not_initialized)
{
  // A controller built directly (not through create()) holds no instance, so
  // inited() is false and run() bails out before the enumeration call.
  VulkanController controller;

  EXPECT_FALSE(controller.run(appCtx));
}

TEST_F(UTEST_VulkanController, run_succeeds_when_device_handler_succeeds)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(true));

  VulkanControllerPtr controller = VulkanController::create();

  ASSERT_NE(controller, nullptr);
  EXPECT_TRUE(controller->run(appCtx));
}

TEST_F(UTEST_VulkanController, run_returns_false_when_device_handler_fails)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(false));

  VulkanControllerPtr controller = VulkanController::create();

  ASSERT_NE(controller, nullptr);
  EXPECT_FALSE(controller->run(appCtx));
}

TEST_F(UTEST_VulkanController, create_returns_null_when_instance_unavailable)
{
  vkmock::fail_instance_creation() = true;

  EXPECT_EQ(VulkanController::create(), nullptr);
}

TEST_F(UTEST_VulkanController, exposes_expected_instance_parameters)
{
  EXPECT_STREQ(VulkanController::applicationName, "cpp-app-template-vulkan-app");
  EXPECT_STREQ(VulkanController::engineName, "cpp-app-template-vulkan-engine");
  const std::uint32_t expectedApiVersion = VK_API_VERSION_1_0;
  EXPECT_EQ(VulkanController::apiVersion, expectedApiVersion);
}
