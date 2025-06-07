cmake_minimum_required(VERSION 3.13)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt6 REQUIRED 
  COMPONENTS Core Gui Qml Quick QuickControls2
)

qt_add_library(
  ${QT6_OBJECT_NAME} OBJECT
  MANUAL_FINALIZATION
  Qt6Initer.cpp
  resources.qrc
  QMLRes.cpp
)

target_include_directories(
  ${QT6_OBJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC Qt6::Core
)

target_link_libraries(
  ${QT6_OBJECT_NAME}
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${QT6_OBJECT_NAME}
)

qt_finalize_target(${QT6_OBJECT_NAME})
