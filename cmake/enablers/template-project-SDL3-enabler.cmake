cmake_minimum_required(VERSION 3.13)

# The SDL3 backend is required for this branch so the enabler always runs.
# Default behaviour: skip find_package(SDL3) and pull SDL3 from FetchContent
# (libsdl-org main release-3.2.10 archive by default). This is the safer
# default for appSDL3 because libsdl3-dev is still missing from older
# distributions. Set SDL3_DISABLE_SYSTEM_PROBE=OFF to let the project probe
# a system-wide SDL3 first and only fall back to FetchContent if missing.

set(TEMPLATE_APP_SDL3_GIT "https://github.com/libsdl-org/SDL.git"
  CACHE STRING "The SDL3 library git source repository")
set(TEMPLATE_APP_SDL3_GIT_TAG "release-3.2.10"
  CACHE STRING "The SDL3 project git repository tag of interest")

option(
  SDL3_DISABLE_SYSTEM_PROBE
  "Skip find_package(SDL3) and pull SDL3 from FetchContent unconditionally"
  ON
)

set(_SDL3_ENABLER_ARGS
  NAME SDL3
  GIT_REPOSITORY ${TEMPLATE_APP_SDL3_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL3_GIT_TAG}
)

if(SDL3_DISABLE_SYSTEM_PROBE)
  list(APPEND _SDL3_ENABLER_ARGS DISABLE_SYSTEM_PROBE)
endif()

template_project_default_3rdparty_enabler(${_SDL3_ENABLER_ARGS})

find_package(OpenGL REQUIRED)

# Normalize the consumer-facing target so dependent code can always link
# against SDL3::SDL3 regardless of whether SDL3 came in via find_package
# (which already defines the imported target) or via FetchContent's
# add_subdirectory (which exposes raw SDL3-shared / SDL3-static targets).
if(NOT TARGET SDL3::SDL3)
  if(TARGET SDL3-shared)
    add_library(SDL3::SDL3 ALIAS SDL3-shared)
  elseif(TARGET SDL3-static)
    add_library(SDL3::SDL3 ALIAS SDL3-static)
  elseif(TARGET SDL3)
    add_library(SDL3::SDL3 ALIAS SDL3)
  endif()
endif()

if(NOT TARGET SDL3::SDL3)
  message(FATAL_ERROR
    "SDL3 enabler ran but no SDL3::SDL3 / SDL3-shared / SDL3-static "
    "target is available. Check the FetchContent build for upstream "
    "errors or install libsdl3-dev on the host.")
endif()
