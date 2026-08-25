cmake_minimum_required(VERSION 3.16)

# Component test: the real QtLogBridge over the real Qt logging with the real
# application logger behind it. The bridge takes the single message handler
# slot of the process once, so the test installs it in an own main() and links
# the GTest::gtest and not the gtest_main one.
add_executable(
  CTEST_QtLogBridge
  CTEST_QtLogBridge.cpp
  ${CMAKE_SOURCE_DIR}/src/qt6/log/QtLogBridge.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_QtLogBridge
  PRIVATE CTEST_QtLogBridge_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_QtLogBridge
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_QtLogBridge
  GTest::gtest GTest::gmock Qt6::Core
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_QtLogBridge
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
