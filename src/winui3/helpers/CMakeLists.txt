cmake_minimum_required(VERSION 3.13)

# WinUI 3 independent helper objects (no Windows App SDK headers required), so
# they build and are unit tested on every platform.
add_library(
  ${WINUI3_OBJECT_NAME}Helpers OBJECT
  WindowConfig.cpp
)

target_include_directories(
  ${WINUI3_OBJECT_NAME}Helpers
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WINUI3_OBJECT_NAME}Helpers
)
