cmake_minimum_required(VERSION 3.13)

# Cocoa (AppKit) dependent main window object, written in Objective-C++. Only
# added on macOS (guarded by the parent CMakeLists), so it always links Cocoa.
add_library(
  ${COCOA_OBJECT_NAME}MainWindow OBJECT
  CocoaMainWindow.mm
)

target_include_directories(
  ${COCOA_OBJECT_NAME}MainWindow
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${COCOA_OBJECT_NAME}MainWindow
  PUBLIC cocoa::sdk
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${COCOA_OBJECT_NAME}MainWindow
)
