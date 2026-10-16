cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_QT6
  "The Qt6 library is mandatory on this branch (no FetchContent available)"
  ON
)

if (NOT ENABLE_QT6)
  message(
    FATAL_ERROR
    "The ENABLE_QT6=OFF is not supported: the Application class runs the "
    "Qt6Controller, so this branch can't be built without the Qt6. "
    "Use the app branch for an application with no Qt6 in it."
  )
endif()

set(CMAKE_AUTOMOC ON)

find_package(
  Qt6 REQUIRED
  COMPONENTS Core Gui Qml Quick QuickControls2 Widgets Charts
)
