cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMongoDBQueryMakerObj OBJECT
  QueryMaker.cpp
  MongoDBConnStringMaker.cpp
)

target_include_directories(
  TemplateMongoDBQueryMakerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MONGOCXX_INCLUDE_DIRS}
    ${BSONCXX_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMongoDBQueryMakerObj
)