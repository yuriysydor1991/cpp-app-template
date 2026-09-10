cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_executable(
  CTEST_app  
  CTEST_app.cpp
  ${CMAKE_SOURCE_DIR}/src/app/applications/Application.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/app/applications/ApplicationHelpPrinter.cpp
  ${CMAKE_SOURCE_DIR}/src/app/CommandLineParser.cpp
  ${CMAKE_SOURCE_DIR}/src/app/applications/ApplicationVersionPrinter.cpp
  ${CMAKE_SOURCE_DIR}/src/app/applications/ApplicationVersionPrinter.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/SignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/ASignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/UserSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PauseSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/PosixSignalsHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/signals-handlers/handlers/posix/StopSignalsHandler.cpp
)

target_include_directories(
  CTEST_app
  PRIVATE
    ${APP_MOCKS_ROOT}/log
    ${APP_MOCKS_ROOT}/LibraryFacade
    ${APP_MOCKS_ROOT}/LibMain
    ${APP_MOCKS_ROOT}/ApplicationContext2LibraryContext
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/lib/facade/public
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
