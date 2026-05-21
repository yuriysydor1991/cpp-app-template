cmake_minimum_required(VERSION 3.13)

# Reusable enabler module for the wxWidgets GUI library.
#
# Kept in a separate file (just like the libcurl and the LibXml2 enablers) so it
# may be reused across components and branches. Including this module exposes
# the imported targets wx::core and wx::base that the component links against.
#
# wxWidgets is not assumed to be installed on the system. The module first
# probes for a ready CMake-package (CONFIG mode) wxWidgets that already exposes
# the wx::core / wx::base imported targets - either a system installation or, for
# the Flatpak package, the dedicated wxWidgets module declared in
# misc/flatpak.conf.json.in. When none is found it falls back to building
# wxWidgets from source through the shared template_project_default_3rdparty_enabler()
# FetchContent helper. On GNU/Linux wxWidgets builds its GTK backend, so the GTK
# development packages are required for that source build (see the requirements
# documentation section).

option(
  ENABLE_WXWIDGETS
  "Enables wxWidgets for the project (a CMake-package one or via FetchContent through the Internet)"
  ON
)

if(NOT ENABLE_WXWIDGETS)
  return()
endif()

set(
  TEMPLATE_APP_WXWIDGETS_GIT "https://github.com/wxWidgets/wxWidgets.git"
  CACHE STRING "The wxWidgets library git source repository"
)
set(
  TEMPLATE_APP_WXWIDGETS_GIT_TAG "v3.3.2"
  CACHE STRING "The wxWidgets project git repository tag of interest"
)

template_project_default_3rdparty_enabler(
    NAME wxWidgets
    GIT_REPOSITORY ${TEMPLATE_APP_WXWIDGETS_GIT}
    GIT_TAG        ${TEMPLATE_APP_WXWIDGETS_GIT_TAG}
)

message(STATUS "The project wxWidgets is made available")
