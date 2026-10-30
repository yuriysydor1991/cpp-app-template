cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateFirebirdObj OBJECT
  Firebird.cpp
)

target_include_directories(
  TemplateFirebirdObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateFirebirdObj
)

add_subdirectory(driver)
add_subdirectory(helpers)
add_subdirectory(sql)
add_subdirectory(tests)
