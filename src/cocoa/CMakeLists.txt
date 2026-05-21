cmake_minimum_required(VERSION 3.13)

# The Cocoa initialization/orchestration object. It is Cocoa free (it only talks
# to the run_cocoa_application() seam), so it builds and is tested on every
# platform; the actual AppKit dependent Objective-C++ code lives in the app and
# main-window subdirectories and only compiles on macOS.
add_library(
  ${COCOA_OBJECT_NAME} OBJECT
  CocoaIniter.cpp
)

target_include_directories(
  ${COCOA_OBJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${COCOA_OBJECT_NAME}
)

add_subdirectory(helpers)
add_subdirectory(app)

# The native Cocoa main window only exists on macOS (and only when the Cocoa
# framework is available); off macOS the app subdirectory builds a stub launch
# seam instead.
if(APPLE AND TARGET cocoa::sdk)
  add_subdirectory(main-window)
endif()

add_subdirectory(tests)
