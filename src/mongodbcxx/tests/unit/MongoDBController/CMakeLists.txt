cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MongoDBController
  UTEST_MongoDBController.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/MongoDBController.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/helpers/QueryMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/helpers/MongoDBConnStringMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/converters/MongoDBDate2String.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_MongoDBController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MongoDBController
  GTest::gtest_main GTest::gmock
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MongoDBController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
