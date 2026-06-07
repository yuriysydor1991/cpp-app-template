cmake_minimum_required(VERSION 3.13)

# Pure unit test: only the unit under test (VulkanController) is compiled,
# against header-replacement mocks (the Vulkan API, the device info handler
# factory and its handler interface, ApplicationContext, log). No real Vulkan
# loader is linked.
add_executable(
  UTEST_VulkanController
  UTEST_VulkanController.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/VulkanController.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_VulkanController
  PRIVATE ${VULKAN_MOCKS_ROOT}/DeviceInfoHandlerFactory
  PRIVATE ${VULKAN_MOCKS_ROOT}/IDeviceInfoHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/vulkan
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_VulkanController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_VulkanController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
