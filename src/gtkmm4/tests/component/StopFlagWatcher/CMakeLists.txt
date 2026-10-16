cmake_minimum_required(VERSION 3.13)

# Component test: the real StopFlagWatcher over a real GIO application main
# loop, which needs no display, unlike the GTK one.
add_executable(
  CTEST_StopFlagWatcher
  CTEST_StopFlagWatcher.cpp
  ${CMAKE_SOURCE_DIR}/src/gtkmm4/StopFlagWatcher.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_StopFlagWatcher
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  CTEST_StopFlagWatcher
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  CTEST_StopFlagWatcher
  GTest::gtest_main GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_StopFlagWatcher
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
