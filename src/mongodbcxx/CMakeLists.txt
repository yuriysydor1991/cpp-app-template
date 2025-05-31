cmake_minimum_required(VERSION 3.13)

include(template-project-mongocxx-available-maker)

add_library(
  TemplateMongoDBCppConnObj OBJECT
  MongoDBController.cpp
)

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
