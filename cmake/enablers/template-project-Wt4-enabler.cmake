cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_WT4
    "Enables the Wt4 web framework for the project usage through system installed one or FetchContent by internet"
    ON
)

option(
    WT4_TRY_SYSTEM_PROBE
    "Set to ON value if current project CMake files should probe the system Wt4 framework"
    ON
)

if (NOT ENABLE_WT4)
    return()
endif()

set(TEMPLATE_APP_WT4_GIT "https://github.com/emweb/wt.git" CACHE STRING "The Wt4 framework git source repository")
set(TEMPLATE_APP_WT4_GIT_TAG "4.11.4" CACHE STRING "The Wt4 project git repository tag of interest")

if (WT4_TRY_SYSTEM_PROBE)
  set(DISABLE_SYSTEM_PROBE "")
  find_package(Wt QUIET)
else()
  set(DISABLE_SYSTEM_PROBE "DISABLE_SYSTEM_PROBE")
endif()

# The Wt defaults build the Dbo database backends, the Qt interworking
# libraries, the examples and the tests, none of which the template uses. The
# disabled set repeats the Wt configure invocation of the
# misc/Dockerfiles/Dockerfile.in, so a fetched Wt matches the docker one.
#
# The names are the Wt ones and some of them are generic enough to collide with
# an option of a project derived from this template, so they are forced onto the
# cache only when the Wt really is about to be built from the sources.
if (NOT Wt_FOUND)
  set(
    TEMPLATE_APP_WT4_DISABLED_FEATURES
    BUILD_EXAMPLES BUILD_TESTS INSTALL_DOCUMENTATION
    ENABLE_LIBWTDBO ENABLE_LIBWTTEST ENABLE_OPENGL ENABLE_PANGO ENABLE_HARU
    ENABLE_SQLITE ENABLE_POSTGRES ENABLE_FIREBIRD ENABLE_MYSQL ENABLE_MSSQLSERVER
    ENABLE_QT4 ENABLE_QT5 ENABLE_QT6
    CONNECTOR_FCGI CONNECTOR_ISAPI
  )

  foreach(wt4DisabledFeature IN LISTS TEMPLATE_APP_WT4_DISABLED_FEATURES)
    set(${wt4DisabledFeature} OFF CACHE BOOL "" FORCE)
  endforeach()

  # The stand-alone httpd connector carries the Wt::WRun server the project runs on.
  set(CONNECTOR_HTTP ON CACHE BOOL "" FORCE)
endif()

template_project_default_3rdparty_enabler(
    NAME Wt
    GIT_REPOSITORY ${TEMPLATE_APP_WT4_GIT}
    GIT_TAG ${TEMPLATE_APP_WT4_GIT_TAG}
    "${DISABLE_SYSTEM_PROBE}"
)

# An installed Wt exports the Wt::Wt and the Wt::HTTP imported targets, while a
# FetchContent build tree declares the plain wt and wthttp ones only. The
# plain names appear in the build tree case exclusively, so they tell the two
# apart and let the project link the namespaced names either way.
if (TARGET wt)
  include(FetchContent)

  FetchContent_GetProperties(Wt SOURCE_DIR WT4_SOURCE_DIR BINARY_DIR WT4_BINARY_DIR)

  # The Wt build tree declares its include directories through the directory
  # scoped INCLUDE_DIRECTORIES command and exports them for the install tree
  # only, so a FetchContent consumer inherits none of them.
  target_include_directories(
    wt INTERFACE
      $<BUILD_INTERFACE:${WT4_SOURCE_DIR}/src>
      $<BUILD_INTERFACE:${WT4_BINARY_DIR}>
  )

  add_library(Wt::Wt ALIAS wt)
  add_library(Wt::HTTP ALIAS wthttp)
endif()

if (NOT TARGET Wt::HTTP)
  message(
    FATAL_ERROR
    "The available Wt4 framework carries no stand-alone httpd connector. "
    "Rebuild the Wt with the CONNECTOR_HTTP option set to ON."
  )
endif()
