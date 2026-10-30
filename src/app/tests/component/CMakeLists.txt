cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_app  
  CTEST_app.cpp
  ${PROJECT_SOURCE_DIR}/src/app/applications/Application.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/app/applications/ApplicationHelpPrinter.cpp
  ${PROJECT_SOURCE_DIR}/src/app/CommandLineParser.cpp
  ${PROJECT_SOURCE_DIR}/src/app/DataLocator.cpp
  ${PROJECT_SOURCE_DIR}/src/app/applications/ApplicationVersionPrinter.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/SignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/ASignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/UserSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PauseSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PosixSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/StopSignalsHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

# The real logger, so the log file effects of the command line are covered too,
# and the mocked llama.cpp controller, so no model takes part.
target_include_directories(
  CTEST_app
  PRIVATE
    ${APP_MOCKS_ROOT}/LlamaCPPController
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_app
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_app
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
