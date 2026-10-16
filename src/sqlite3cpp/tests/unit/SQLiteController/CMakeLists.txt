cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SQLiteController
  UTEST_SQLiteController.cpp
  ${CMAKE_SOURCE_DIR}/src/sqlite3cpp/SQLiteController.cpp
  ${CMAKE_SOURCE_DIR}/src/sqlite3cpp/sqlmaker/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SQLiteController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${APP_MOCKS_ROOT}/project-global-decls
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_SQLiteController
  GTest::gtest_main GTest::gmock SQLiteCpp sqlite3 pthread dl
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SQLiteController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
