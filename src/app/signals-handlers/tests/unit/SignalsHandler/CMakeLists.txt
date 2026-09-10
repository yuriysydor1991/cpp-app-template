cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SignalsHandler
  UTEST_SignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/SignalsHandler.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SignalsHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/ContinueSignalsHandler
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/IgnoredSignalsHandler
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/PauseSignalsHandler
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/ReloadSignalsHandler
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/StopSignalsHandler
  PRIVATE ${POSIX_SIGNALS_HANDLERS_MOCKS_ROOT}/UserSignalsHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_SignalsHandler
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SignalsHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
