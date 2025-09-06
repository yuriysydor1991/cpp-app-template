cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(
  ${PROJECT_LIBRARY_NAME}
  SHARED
)

target_include_directories(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/facade/public>
    $<INSTALL_INTERFACE:include/${PROJECT_LIBRARY_NAME}>
)

set_target_properties(
  ${PROJECT_LIBRARY_NAME}
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(
  TARGETS ${PROJECT_LIBRARY_NAME}
  LIBRARY
    DESTINATION lib
    COMPONENT Runtime
    NAMELINK_COMPONENT Development
)

add_subdirectory(facade)
add_subdirectory(libmain)

include(lib-cmake-module-gen)

