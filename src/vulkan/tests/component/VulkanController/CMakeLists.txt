cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_VulkanController
  CTEST_VulkanController.cpp
  ${PROJECT_SOURCE_DIR}/src/vulkan/VulkanController.cpp
  ${PROJECT_SOURCE_DIR}/src/vulkan/device-info/DeviceInfoHandlerFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/vulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  CTEST_VulkanController
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_VulkanController
  GTest::gtest_main GTest::gmock ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_VulkanController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
