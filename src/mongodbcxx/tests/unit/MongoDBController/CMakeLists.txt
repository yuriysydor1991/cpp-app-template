cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MongoDBController
  UTEST_MongoDBController.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/MongoDBController.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/helpers/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/helpers/MongoDBConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/converters/MongoDBDate2String.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_MongoDBController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${MONGODB_MOCKS_ROOT}
  PRIVATE ${CMAKE_SOURCE_DIR}
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
