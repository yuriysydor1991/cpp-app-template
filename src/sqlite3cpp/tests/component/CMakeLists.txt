cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_SQLiteController
  CTEST_SQLiteController.cpp
  ${PROJECT_SOURCE_DIR}/src/sqlite3cpp/SQLiteController.cpp
  ${PROJECT_SOURCE_DIR}/src/sqlite3cpp/sqlmaker/QueryMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_SQLiteController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_SQLiteController
  GTest::gtest_main GTest::gmock SQLiteCpp sqlite3 pthread dl
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_SQLiteController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
