cmake_minimum_required(VERSION 3.13)

# The libcurl is a hard requirement of this branch rather than an optional
# integration: the application downloads it's data with it.
if (NOT TARGET CURL::libcurl)
  message(
    FATAL_ERROR
    "The CURLController performs it's requests with the libcurl. Keep the "
    "ENABLE_LIBCURL option ON."
  )
endif()

add_library(
  TemplateProjectCURLControllerObj OBJECT
  CURLController.cpp
  HeadersList.cpp
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
  PRIVATE TemplateProjectCURLControllerObj
)

add_subdirectory(tests)
