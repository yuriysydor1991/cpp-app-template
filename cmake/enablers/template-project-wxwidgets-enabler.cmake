cmake_minimum_required(VERSION 3.13)

# Reusable enabler module for the wxWidgets GUI library.
#
# Kept in a separate file (just like the libcurl and the LibXml2 enablers) so it
# may be reused across components and branches. Including this module exposes
# the imported targets wx::core and wx::base that the component links against.
#
# wxWidgets is not assumed to be installed on the system, therefore the module
# probes for a CMake-package enabled system installation first and otherwise
# downloads and builds wxWidgets from source through the CMake FetchContent
# facility. On GNU/Linux wxWidgets builds its GTK backend, so the GTK
# development packages are required for the FetchContent build (see the
# requirements documentation section).

option(
  ENABLE_WXWIDGETS
  "Enables wxWidgets for the project (system installed one or via FetchContent through the Internet)"
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
  TEMPLATE_APP_WXWIDGETS_GIT_TAG "v3.2.6"
  CACHE STRING "The wxWidgets project git repository tag of interest"
)

option(
  WXWIDGETS_TRY_SYSTEM_PROBE
  "Set to ON to probe for a CMake-package enabled system wxWidgets before FetchContent"
  ON
)

if(WXWIDGETS_TRY_SYSTEM_PROBE)
  message(STATUS "Trying to probe a system installed wxWidgets")
  find_package(wxWidgets CONFIG QUIET COMPONENTS core base)
endif()

if(TARGET wx::core)
  message(STATUS "The system already provides the wxWidgets library")
else()
  message(STATUS "The wxWidgets library is not available in the system (or probing is OFF)")
  message(STATUS "Trying to make wxWidgets available through the Internet")
  message(STATUS "wxWidgets URL: ${TEMPLATE_APP_WXWIDGETS_GIT}")
  message(STATUS "wxWidgets Tag: ${TEMPLATE_APP_WXWIDGETS_GIT_TAG}")

  # wxWidgets releases still declare a pre-3.5 cmake_minimum_required, which the
  # CMake 4.x policy engine rejects; allow the fetched build to configure anyway.
  if(NOT DEFINED CMAKE_POLICY_VERSION_MINIMUM)
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
  endif()

  # Keep the produced wxWidgets build as small as practical.
  set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
  set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
  set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(wxBUILD_DEMOS OFF CACHE BOOL "" FORCE)
  set(wxBUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)

  include(FetchContent)

  FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY ${TEMPLATE_APP_WXWIDGETS_GIT}
    GIT_TAG        ${TEMPLATE_APP_WXWIDGETS_GIT_TAG}
    GIT_SHALLOW    TRUE
  )

  FetchContent_MakeAvailable(wxWidgets)
endif()

message(STATUS "The project wxWidgets is made available")
