cmake_minimum_required(VERSION 3.13)

# The SDL2 backend is required for this branch so the enabler always runs.
# Use SDL2_DISABLE_SYSTEM_PROBE=ON to skip find_package(SDL2) and pull SDL2
# from the upstream git repository via FetchContent instead. This is the
# escape hatch for hosts where no usable libsdl2-dev is available.

set(TEMPLATE_APP_SDL2_GIT "https://github.com/libsdl-org/SDL.git"
  CACHE STRING "The SDL2 library git source repository")
set(TEMPLATE_APP_SDL2_GIT_TAG "release-2.30.10"
  CACHE STRING "The SDL2 project git repository tag of interest")

option(
  SDL2_DISABLE_SYSTEM_PROBE
  "Skip find_package(SDL2) and pull SDL2 from FetchContent unconditionally"
  OFF
)

set(_SDL2_ENABLER_ARGS
  NAME SDL2
  GIT_REPOSITORY ${TEMPLATE_APP_SDL2_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL2_GIT_TAG}
)

if(SDL2_DISABLE_SYSTEM_PROBE)
  list(APPEND _SDL2_ENABLER_ARGS DISABLE_SYSTEM_PROBE)
endif()

template_project_default_3rdparty_enabler(${_SDL2_ENABLER_ARGS})

find_package(OpenGL REQUIRED)

# Normalize the consumer-facing target so dependent code can always link
# against SDL2::SDL2 regardless of whether SDL2 came in via find_package
# (which already defines the imported target) or via FetchContent's
# add_subdirectory (which exposes raw SDL2 / SDL2-static targets).
if(NOT TARGET SDL2::SDL2)
  if(TARGET SDL2)
    add_library(SDL2::SDL2 ALIAS SDL2)
  elseif(TARGET SDL2-static)
    add_library(SDL2::SDL2 ALIAS SDL2-static)
  endif()
endif()

if(NOT TARGET SDL2::SDL2)
  message(FATAL_ERROR
    "SDL2 enabler ran but no SDL2::SDL2 / SDL2 / SDL2-static target is "
    "available. Check the FetchContent build for upstream errors or "
    "install libsdl2-dev on the host.")
endif()
