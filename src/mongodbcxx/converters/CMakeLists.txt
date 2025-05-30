cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMongoDBTypeConvertersObj OBJECT
  MongoDBDate2String.cpp
)

target_include_directories(
  TemplateMongoDBTypeConvertersObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MONGOCXX_INCLUDE_DIRS}
    ${BSONCXX_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMongoDBTypeConvertersObj
)