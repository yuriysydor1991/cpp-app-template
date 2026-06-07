cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PhysicalDeviceInfoHandler
  UTEST_PhysicalDeviceInfoHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  UTEST_PhysicalDeviceInfoHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/vulkan
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_PhysicalDeviceInfoHandler
  GTest::gtest_main GTest::gmock
)

# The handler source is compiled against the header-only Vulkan mock
# (${GENERAL_MOCKS_ROOT}/vulkan); the real Vulkan loader is intentionally not
# linked for the unit tier. The live runtime path is covered by the component
# test.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PhysicalDeviceInfoHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
