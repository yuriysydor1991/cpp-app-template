cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_UserSignalsHandler
  UTEST_UserSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/UserSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PosixSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/ASignalsHandler.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_UserSignalsHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_UserSignalsHandler
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_UserSignalsHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
