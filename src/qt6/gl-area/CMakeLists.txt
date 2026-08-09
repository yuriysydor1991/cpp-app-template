cmake_minimum_required(VERSION 3.16)

# The raw OpenGL calls are dispatched through the QtOpenGL module classes, so
# the QML item below needs no GL loader of its own. The item is a plain C++
# class registered into QML by the Qt6Initer, hence no QML module is declared
# here.
qt6_add_library(
  ${QT6_OBJECT_NAME}glarea STATIC
  GLTriangleItem.cpp
  GLTriangleRenderer.cpp
)

target_include_directories(
  ${QT6_OBJECT_NAME}glarea
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${QT6_OBJECT_NAME}glarea
  PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::Qml
    Qt6::Quick
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}glarea
)
