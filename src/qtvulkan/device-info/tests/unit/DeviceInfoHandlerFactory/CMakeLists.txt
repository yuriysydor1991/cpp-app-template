cmake_minimum_required(VERSION 3.16)

add_executable(
  UTEST_DeviceInfoHandlerFactory
  UTEST_DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/device-info/DeviceInfoHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  UTEST_DeviceInfoHandlerFactory
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_DeviceInfoHandlerFactory
  GTest::gtest_main GTest::gmock Qt6::Core Qt6::Gui ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DeviceInfoHandlerFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
