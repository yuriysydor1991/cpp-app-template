cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_app  
  CTEST_app.cpp
  ${CMAKE_SOURCE_DIR}/src/app/Application.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationHelpPrinter.cpp
  ${CMAKE_SOURCE_DIR}/src/app/CommandLineParser.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationVersionPrinter.cpp
)

target_include_directories(
  CTEST_app
  PRIVATE
    ${APP_MOCKS_ROOT}/log
    ${APP_MOCKS_ROOT}/PgSQL
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
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
