cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectCURLControllerObj OBJECT
  CURLController.cpp
)

target_include_directories(
  TemplateProjectCURLControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The libcurl itself is made available by the libcurl enabler. The PUBLIC
# keyword hands its headers over to the sources above and its library over to
# the executable which links this object library.
target_link_libraries(
  TemplateProjectCURLControllerObj
  PUBLIC CURL::libcurl
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectCURLControllerObj
)

add_subdirectory(tests)
