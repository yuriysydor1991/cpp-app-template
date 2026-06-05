#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <QVulkanInstance>

#include "src/qtvulkan/QtVulkanController.h"
#include "src/qtvulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"

using namespace testing;
using namespace qtvulkani;

namespace
{

/**
 * @brief Test double exposing the protected seams so run()'s orchestration may
 * be exercised without a live Vulkan runtime: inited() is forced true and the
 * instance pointer handed to the (mocked) handler is an unused nullptr.
 */
class TestableQtVulkanController : public QtVulkanController
{
 protected:
  bool init() override { return true; }
  bool inited() const override { return true; }
  QVulkanInstance* instance_ptr() override { return nullptr; }
};

}  // namespace

class UTEST_QtVulkanController : public Test
{
 public:
  UTEST_QtVulkanController()
      : handler{std::make_shared<NiceMock<IDeviceInfoHandler>>()}
  {
    // The controller builds a DeviceInfoHandlerFactory internally; route every
    // created factory to hand out the fixture's mock handler.
    DeviceInfoHandlerFactory::onMockCreate = [this](
                                                 DeviceInfoHandlerFactory& f) {
      EXPECT_CALL(f, create_default_handler()).WillRepeatedly(Return(handler));
    };
  }

  ~UTEST_QtVulkanController() override
  {
    DeviceInfoHandlerFactory::onMockCreate = nullptr;
  }

  std::shared_ptr<NiceMock<IDeviceInfoHandler>> handler;
};

TEST_F(UTEST_QtVulkanController, run_returns_false_when_not_initialized)
{
  // A controller built directly (not through create()) holds no Vulkan
  // instance, so inited() is false and run() bails out before the enumeration.
  QtVulkanController controller;

  EXPECT_FALSE(controller.run());
}

TEST_F(UTEST_QtVulkanController, run_succeeds_when_device_handler_succeeds)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(true));

  TestableQtVulkanController controller;

  EXPECT_TRUE(controller.run());
}

TEST_F(UTEST_QtVulkanController, run_returns_false_when_device_handler_fails)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(false));

  TestableQtVulkanController controller;

  EXPECT_FALSE(controller.run());
}
