cmake_minimum_required(VERSION 3.16)

qt6_add_library(
  ${QT6_OBJECT_NAME} STATIC
  Qt6Initer.cpp
)

target_include_directories(
  ${QT6_OBJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${QT6_OBJECT_NAME}
  PUBLIC
    Qt6::Core
    Qt6::DBus
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}
)
