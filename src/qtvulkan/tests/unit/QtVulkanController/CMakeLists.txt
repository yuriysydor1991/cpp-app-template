cmake_minimum_required(VERSION 3.16)

# Pure unit test: only the unit under test (QtVulkanController) is compiled,
# against header-replacement mocks (the device info handler factory and its
# handler interface, log). The native Qt6::Gui is real (it ships with qt6-base)
# but no live Vulkan runtime is touched - run()'s orchestration is driven
# through the mocks and the overridden seams.
add_executable(
  UTEST_QtVulkanController
  UTEST_QtVulkanController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtvulkan/QtVulkanController.cpp
)

target_include_directories(
  UTEST_QtVulkanController
  PRIVATE ${QTVULKAN_MOCKS_ROOT}/DeviceInfoHandlerFactory
  PRIVATE ${QTVULKAN_MOCKS_ROOT}/IDeviceInfoHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_QtVulkanController
  GTest::gtest_main GTest::gmock Qt6::Core Qt6::Gui ${VULKAN_LINK_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_QtVulkanController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
