cmake_minimum_required(VERSION 3.16)

# Component test: the real QtVulkanController, factory and handler are exercised
# against the system Vulkan runtime through the native Qt QVulkanInstance. A
# QGuiApplication is required by the platform Vulkan integration, so the test
# provides its own main() and links GTest::gtest (not gtest_main).
add_executable(
  CTEST_QtVulkanController
  CTEST_QtVulkanController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/QtVulkanController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/device-info/DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  CTEST_QtVulkanController
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_QtVulkanController
  GTest::gtest GTest::gmock Qt6::Core Qt6::Gui ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_QtVulkanController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
