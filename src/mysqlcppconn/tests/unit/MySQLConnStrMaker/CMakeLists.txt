cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MySQLConnStrMaker
  UTEST_MySQLConnStrMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mysqlcppconn/helpers/MySQLConnStrMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_MySQLConnStrMaker
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MySQLConnStrMaker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MySQLConnStrMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
