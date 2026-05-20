cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_WxWidgets
  CTEST_WxWidgets.cpp
  ${CMAKE_SOURCE_DIR}/src/wxwidgets/WxWidgetsIniter.cpp
  ${CMAKE_SOURCE_DIR}/src/wxwidgets/helpers/WindowConfig.cpp
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
