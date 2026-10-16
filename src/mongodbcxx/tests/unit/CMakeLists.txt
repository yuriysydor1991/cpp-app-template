cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(MongoDBConnStringMaker)
add_subdirectory(QueryMaker)
add_subdirectory(MongoDBDate2String)
add_subdirectory(MongoDBController)
