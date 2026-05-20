cmake_minimum_required(VERSION 3.13)

# wxWidgets independent helper objects (no wxWidgets headers required).
add_library(
  ${WXWIDGETS_OBJECT_NAME}Helpers OBJECT
  WindowConfig.cpp
)

target_include_directories(
  ${WXWIDGETS_OBJECT_NAME}Helpers
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WXWIDGETS_OBJECT_NAME}Helpers
)
