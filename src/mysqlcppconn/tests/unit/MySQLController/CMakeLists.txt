cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MySQLController
  UTEST_MySQLController.cpp
  ${CMAKE_SOURCE_DIR}/src/mysqlcppconn/MySQLController.cpp
  ${CMAKE_SOURCE_DIR}/src/mysqlcppconn/sql/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mysqlcppconn/helpers/MySQLConnStrMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_MySQLController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${MYSQL_MOCKS_ROOT}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  UTEST_MySQLController
  GTest::gtest_main GTest::gmock ${MySQL_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MySQLController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
