cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectDBusServerObjectsObj OBJECT
  CurrentDateServerObject.cpp
  DBusServerObjectFactory.cpp
)

target_include_directories(
  TemplateProjectDBusServerObjectsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectDBusServerObjectsObj
)

add_subdirectory(tests)
