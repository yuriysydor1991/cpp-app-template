cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_Firebird
  CTEST_Firebird.cpp
  ${PROJECT_SOURCE_DIR}/src/Firebird/Firebird.cpp
  ${PROJECT_SOURCE_DIR}/src/Firebird/sql/QueryMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/Firebird/helpers/FbConnStringMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_Firebird
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_Firebird
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Firebird
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
