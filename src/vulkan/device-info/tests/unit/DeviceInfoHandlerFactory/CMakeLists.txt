cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DeviceInfoHandlerFactory
  UTEST_DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  UTEST_DeviceInfoHandlerFactory
  PRIVATE ${GENERAL_MOCKS_ROOT}/vulkan
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_DeviceInfoHandlerFactory
  GTest::gtest_main GTest::gmock
)

# The factory and handler sources are compiled against the header-only Vulkan
# mock (${GENERAL_MOCKS_ROOT}/vulkan); the real Vulkan loader is intentionally
# not linked for the unit tier.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DeviceInfoHandlerFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
