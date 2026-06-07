cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_PhysicalDeviceInfoHandler
  CTEST_PhysicalDeviceInfoHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/PhysicalDeviceInfoHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/vulkan/device-info/DeviceInfoHandlerFactory.cpp
)

target_include_directories(
  CTEST_PhysicalDeviceInfoHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_PhysicalDeviceInfoHandler
  GTest::gtest_main GTest::gmock ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_PhysicalDeviceInfoHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
