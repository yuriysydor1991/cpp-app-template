cmake_minimum_required(VERSION 3.13)

# The only object that links against the native Firebird client library.
# The Firebird::fbclient imported target is provided by the reusable
# cmake/enablers/template-project-firebird-enabler.cmake module.

add_library(
  TemplateFirebirdDriverObj OBJECT
  FbClient.cpp
)

target_include_directories(
  TemplateFirebirdDriverObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateFirebirdDriverObj
  PRIVATE
    Firebird::fbclient
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateFirebirdDriverObj Firebird::fbclient
)
