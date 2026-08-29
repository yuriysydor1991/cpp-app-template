cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMongoDBCppConnObj OBJECT
  MongoDBController.cpp
)

target_include_directories(
  TemplateMongoDBCppConnObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The imported targets are linked and not the plain mongocxx and bsoncxx
# library names, because since the C++ driver 4.4.0 the library file names
# carry the ABI version number (libmongocxx1.so, libbsoncxx1.so) and the plain
# names are not resolvable by the linker anymore.
target_link_libraries(
  TemplateMongoDBCppConnObj
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMongoDBCppConnObj
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

add_subdirectory(helpers)
add_subdirectory(converters)
