cmake_minimum_required(VERSION 3.13)

# Cocoa independent helper objects (no AppKit headers required), so they build
# and are unit tested on every platform.
add_library(
  ${COCOA_OBJECT_NAME}Helpers OBJECT
  WindowConfig.cpp
)

target_include_directories(
  ${COCOA_OBJECT_NAME}Helpers
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${COCOA_OBJECT_NAME}Helpers
)
