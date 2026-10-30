cmake_minimum_required(VERSION 3.13)

# Component test: the map page in the very GResource bundle of the binary. The
# web view itself needs an opened display, so it is left to the manual runs.
add_executable(
  CTEST_Map
  CTEST_Map.cpp
)

target_include_directories(
  CTEST_Map
  PRIVATE
    ${GTKMM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_directories(
  CTEST_Map
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

# The bundle registers itself on load.
target_link_libraries(
  CTEST_Map
  gresourcelib
  ${GTKMM_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Map
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
