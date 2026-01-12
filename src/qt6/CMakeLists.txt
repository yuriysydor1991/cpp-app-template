cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt6 REQUIRED 
  COMPONENTS Core Gui Qml Quick QuickControls2
)

qt6_add_library(
  ${QT6_OBJECT_NAME} STATIC
  Qt6Initer.cpp
  QMLRes.cpp
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
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}
)

add_subdirectory(ui)
