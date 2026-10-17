cmake_minimum_required(VERSION 3.13)

# Component test: the real dma-buf renderer on the real instance of the real
# VulkanController; the live part is skipped without a Vulkan runtime.
add_executable(
  CTEST_VulkanDmabufRenderer
  CTEST_VulkanDmabufRenderer.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/dmabuf/VulkanDmabufRenderer.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/VulkanController.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  CTEST_VulkanDmabufRenderer
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_VulkanDmabufRenderer
  GTest::gtest_main GTest::gmock ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_VulkanDmabufRenderer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
