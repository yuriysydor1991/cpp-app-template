cmake_minimum_required(VERSION 3.16)

# Pure unit test: the handle() orchestration is exercised against an overridden
# fetch_devices() seam, so no live Vulkan runtime is touched. Qt6::Gui is linked
# only because the (unused at run time) real fetch_devices() is compiled in.
add_executable(
  UTEST_PhysicalDeviceInfoHandler
  UTEST_PhysicalDeviceInfoHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/device-info/PhysicalDeviceInfoHandler.cpp
)

target_include_directories(
  UTEST_PhysicalDeviceInfoHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_PhysicalDeviceInfoHandler
  GTest::gtest_main GTest::gmock Qt6::Core Qt6::Gui ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PhysicalDeviceInfoHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
