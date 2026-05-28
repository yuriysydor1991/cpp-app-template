cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SFML
    "Enables the SFML library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_SFML)
    return()
endif()

set(TEMPLATE_APP_SFML_GIT "https://github.com/SFML/SFML.git" CACHE STRING "The SFML library git source repository")
set(TEMPLATE_APP_SFML_GIT_TAG "2.6.2" CACHE STRING "The SFML library git source repository tag")

# Keep the FetchContent build lean: the template's SFML component only needs the
# graphics/window/system modules, so skip audio (drags in extra codecs) and
# network (drags in TLS) as well as the upstream examples and documentation.
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

# Probes the system installed SFML (COMPONENTS graphics window system) first and
# falls back to fetching and building it from the upstream git repository.
template_project_default_3rdparty_enabler(
  NAME SFML
  GIT_REPOSITORY ${TEMPLATE_APP_SFML_GIT}
  GIT_TAG        ${TEMPLATE_APP_SFML_GIT_TAG}
  COMPONENTS     graphics window system
)

if(NOT TARGET sfml-graphics)
  message(FATAL_ERROR
    "SFML enabler ran but no sfml-graphics target is available. Check the "
    "FetchContent build for upstream errors or install libsfml-dev on the host.")
endif()
