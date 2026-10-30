cmake_minimum_required(VERSION 3.13)

# The only object that links against the native Firebird client library.
# The Firebird::fbclient imported target is provided by the reusable
# cmake/enablers/template-project-firebird-enabler.cmake module. With the
# ENABLE_FIREBIRD option OFF the DisabledFbClient stands in for the driver, so
# the project builds without the library.

if (ENABLE_FIREBIRD)
  add_library(
    TemplateFirebirdDriverObj OBJECT
    FbClient.cpp
    FbDpbBuilder.cpp
  )

  target_link_libraries(
    TemplateFirebirdDriverObj
    PRIVATE
      Firebird::fbclient
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    PRIVATE TemplateFirebirdDriverObj Firebird::fbclient
  )
else()
  add_library(
    TemplateFirebirdDriverObj OBJECT
    DisabledFbClient.cpp
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    PRIVATE TemplateFirebirdDriverObj
  )
endif()

target_include_directories(
  TemplateFirebirdDriverObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)
