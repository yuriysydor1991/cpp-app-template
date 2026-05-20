cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Firebird
  UTEST_Firebird.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/Firebird.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/sql/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/helpers/FbConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_Firebird
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Firebird
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Firebird
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
