cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_IgnoredSignalsHandler
  UTEST_IgnoredSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PosixSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/ASignalsHandler.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_IgnoredSignalsHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_IgnoredSignalsHandler
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_IgnoredSignalsHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
