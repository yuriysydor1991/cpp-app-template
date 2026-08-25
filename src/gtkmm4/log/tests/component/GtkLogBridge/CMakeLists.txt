cmake_minimum_required(VERSION 3.13)

# Component test: the real GtkLogBridge over the real GLib logging with the
# real application logger behind it. The GLib accepts a writer only once in the
# life of a process, so the test installs the bridge in an own main() and links
# the GTest::gtest and not the gtest_main one.
add_executable(
  CTEST_GtkLogBridge
  CTEST_GtkLogBridge.cpp
  ${CMAKE_SOURCE_DIR}/src/gtkmm4/log/GtkLogBridge.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_GtkLogBridge
  PRIVATE CTEST_GtkLogBridge_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_GtkLogBridge
  PRIVATE
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  CTEST_GtkLogBridge
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  CTEST_GtkLogBridge
  GTest::gtest GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_GtkLogBridge
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
