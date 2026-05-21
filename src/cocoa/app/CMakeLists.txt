cmake_minimum_required(VERSION 3.13)

# The Cocoa application object defines the run_cocoa_application() launch seam.
# On macOS (with the Cocoa framework available through cocoa::sdk) it is the real
# Objective-C++ AppKit application; on every other platform it is a small stub so
# the executable still links and runs.
if(APPLE AND TARGET cocoa::sdk)
  add_library(${COCOA_OBJECT_NAME}App OBJECT CocoaApp.mm)
  target_link_libraries(${COCOA_OBJECT_NAME}App PUBLIC cocoa::sdk)
else()
  add_library(${COCOA_OBJECT_NAME}App OBJECT CocoaAppStub.cpp)
endif()

target_include_directories(
  ${COCOA_OBJECT_NAME}App
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${COCOA_OBJECT_NAME}App
)
