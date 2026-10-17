cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_WxWidgets
  CTEST_WxWidgets.cpp
  ${CMAKE_SOURCE_DIR}/src/wxwidgets/WxWidgetsController.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_WxWidgets
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_WxWidgets
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_WxWidgets
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)

# The real stop flag watcher over a real wxWidgets console application main
# loop, which needs no display, unlike the GUI one.
add_executable(
  CTEST_WxStopFlagWatcher
  CTEST_WxStopFlagWatcher.cpp
  ${CMAKE_SOURCE_DIR}/src/wxwidgets/app/StopFlagWatcher.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_WxStopFlagWatcher
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_WxStopFlagWatcher
  GTest::gtest_main GTest::gmock wx::core wx::base
)

gtest_add_tests(
  TARGET CTEST_WxStopFlagWatcher
  TEST_SUFFIX .noArgs
  TEST_LIST watcherTests
)

set_tests_properties(
  ${watcherTests}
  PROPERTIES
    TIMEOUT 600
    ENVIRONMENT
      "LSAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/CTEST_WxStopFlagWatcher.lsan.supp"
)
