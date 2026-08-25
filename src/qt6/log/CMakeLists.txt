cmake_minimum_required(VERSION 3.16)

# The bridge speaks to the Qt logging alone, which lives in the Qt6::Core
# module, and it declares no QObject of it's own, so nothing of the meta object
# compiler is involved here.
qt6_add_library(
  ${QT6_OBJECT_NAME}log STATIC
  QtLogBridge.cpp
)

target_include_directories(
  ${QT6_OBJECT_NAME}log
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${QT6_OBJECT_NAME}log
  PUBLIC
    Qt6::Core
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}log
)

add_subdirectory(tests)
