#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/qtvulkan/device-info/DeviceInfoHandlerFactory.h"
#include "src/qtvulkan/device-info/IDeviceInfoHandler.h"
#include "src/qtvulkan/device-info/PhysicalDeviceInfoHandler.h"

using namespace testing;
using namespace qtvulkani;

class UTEST_DeviceInfoHandlerFactory : public Test
{
 public:
  UTEST_DeviceInfoHandlerFactory()
      : factory{std::make_shared<DeviceInfoHandlerFactory>()}
  {
  }

  std::shared_ptr<DeviceInfoHandlerFactory> factory;
};

TEST_F(UTEST_DeviceInfoHandlerFactory, create_physical_device_handler_not_null)
{
  IDeviceInfoHandlerPtr handler = factory->create_physical_device_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(UTEST_DeviceInfoHandlerFactory,
       create_physical_device_handler_is_physical)
{
  IDeviceInfoHandlerPtr handler = factory->create_physical_device_handler();

  EXPECT_NE(std::dynamic_pointer_cast<PhysicalDeviceInfoHandler>(handler),
            nullptr);
}

TEST_F(UTEST_DeviceInfoHandlerFactory, create_default_handler_not_null)
{
  IDeviceInfoHandlerPtr handler = factory->create_default_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(UTEST_DeviceInfoHandlerFactory, create_default_handler_is_physical)
{
  IDeviceInfoHandlerPtr handler = factory->create_default_handler();

  // For now the default handler must be the physical device info handler.
  EXPECT_NE(std::dynamic_pointer_cast<PhysicalDeviceInfoHandler>(handler),
            nullptr);
}
