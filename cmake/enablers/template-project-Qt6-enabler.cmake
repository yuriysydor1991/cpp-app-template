cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_QT6 
  "If to enable the Qt6 library (no FetchContent available)"
  ON
)

if (NOT ENABLE_QT6)
  return()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt6 REQUIRED
  COMPONENTS Core Gui Qml Quick QuickControls2 WebEngineQuick
)
