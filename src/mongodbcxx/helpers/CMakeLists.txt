cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMongoDBQueryMakerObj OBJECT
  QueryMaker.cpp
  MongoDBConnStringMaker.cpp
)

target_include_directories(
  TemplateMongoDBQueryMakerObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateMongoDBQueryMakerObj
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateMongoDBQueryMakerObj
)