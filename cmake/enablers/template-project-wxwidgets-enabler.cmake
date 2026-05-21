cmake_minimum_required(VERSION 3.13)

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

find_package(wxWidgets CONFIG QUIET COMPONENTS core base)

if(TARGET wx::core)
  message(STATUS "The system already provides the wxWidgets library")
else()
  message(STATUS "The wxWidgets library is not available as a CMake package")
  message(STATUS "Building wxWidgets ${TEMPLATE_APP_WXWIDGETS_GIT_TAG} from source through the Internet")

  # DISABLE_SYSTEM_PROBE: the CONFIG probe above is the system probe; the shared
  # helper must not re-probe in MODULE mode (it would match a system wxWidgets
  # without exposing the wx::core / wx::base targets and skip the source build).
  template_project_default_3rdparty_enabler(
      DISABLE_SYSTEM_PROBE
      NAME wxWidgets
      GIT_REPOSITORY ${TEMPLATE_APP_WXWIDGETS_GIT}
      GIT_TAG        ${TEMPLATE_APP_WXWIDGETS_GIT_TAG}
  )
endif()

message(STATUS "The project wxWidgets is made available")
