cmake_minimum_required(VERSION 3.13)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

add_library(
  TemplateMongoDBCppConnObj OBJECT
  MongoDBController.cpp
)

get_target_property(MONGOCXX_INCLUDE_DIRS mongo::mongocxx_shared INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(BSONCXX_INCLUDE_DIRS mongo::bsoncxx_shared INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "mongocxx include dirs: ${MONGOCXX_INCLUDE_DIRS}")
message(STATUS "bsoncxx include dirs: ${BSONCXX_INCLUDE_DIRS}")

target_include_directories(
  TemplateMongoDBCppConnObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MONGOCXX_INCLUDE_DIRS}
    ${BSONCXX_INCLUDE_DIRS}
)

target_include_directories(
  ${PROJECT_BINARY_NAME} 
  PRIVATE
    ${MONGOCXX_INCLUDE_DIRS}
    ${BSONCXX_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMongoDBCppConnObj
  mongocxx bsoncxx
)

add_subdirectory(helpers)
add_subdirectory(converters)
