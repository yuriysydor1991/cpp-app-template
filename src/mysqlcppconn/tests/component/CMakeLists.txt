cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_MySQLController
  CTEST_MySQLController.cpp
  ${PROJECT_SOURCE_DIR}/src/mysqlcppconn/MySQLController.cpp
  ${PROJECT_SOURCE_DIR}/src/mysqlcppconn/sql/QueryMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/mysqlcppconn/helpers/MySQLConnStrMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_MySQLController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
  PRIVATE ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  CTEST_MySQLController
  GTest::gtest_main GTest::gmock ${MySQL_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_MySQLController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 120)
