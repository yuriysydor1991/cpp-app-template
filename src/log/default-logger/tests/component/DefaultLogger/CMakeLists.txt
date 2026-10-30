cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_DefaultLogger
  CTEST_DefaultLogger.cpp
  CTEST_DefaultLoggerRealLogger.cpp
  GlobalLocaleGuard.cpp
  GroupingNumpunct.cpp
  RecordingLogger.cpp
  RecordingRealLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_DefaultLogger
  PRIVATE CTEST_DefaultLogger_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_DefaultLogger
  PRIVATE 
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_DefaultLogger
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_DefaultLogger
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
