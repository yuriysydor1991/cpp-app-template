cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_ContinueSignalsHandler
  UTEST_ContinueSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PosixSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/ASignalsHandler.cpp
  ${GLOBAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_ContinueSignalsHandler
  PRIVATE ${GLOBAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GLOBAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_ContinueSignalsHandler
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ContinueSignalsHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
