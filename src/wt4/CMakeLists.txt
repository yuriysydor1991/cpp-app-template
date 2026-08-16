cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateWt4Obj OBJECT
  Wt4Server.cpp
  Wt4Context.cpp
)

target_include_directories(
  TemplateWt4Obj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The Wt4 framework itself is made available by the Wt4 enabler. The PUBLIC
# keyword hands its headers over to the sources above and its libraries over to
# the executable which links this object library.
target_link_libraries(
  TemplateWt4Obj
  PUBLIC Wt::Wt Wt::HTTP
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4Obj
)

add_subdirectory(widgets)
