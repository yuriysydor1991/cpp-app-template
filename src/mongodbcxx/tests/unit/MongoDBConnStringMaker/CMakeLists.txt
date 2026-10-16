cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MongoDBConnStringMaker
  UTEST_MongoDBConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/helpers/MongoDBConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_MongoDBConnStringMaker
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MongoDBConnStringMaker
  GTest::gtest_main GTest::gmock
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MongoDBConnStringMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
