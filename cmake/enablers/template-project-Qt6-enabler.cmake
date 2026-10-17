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

# The AUTOMOC (CMake 3.30 and newer) checks every link dependency of the binary
# from the src directory, which sees no imported target the enablers find in
# the top level directory after it (the OpenSSL, libcurl, libxml2 ones), so the
# found package targets are made global (CMake 3.24 and newer).
set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL ON)

find_package(
  Qt6 REQUIRED
  COMPONENTS Core Gui Qml Quick QuickControls2 Location Positioning
)
