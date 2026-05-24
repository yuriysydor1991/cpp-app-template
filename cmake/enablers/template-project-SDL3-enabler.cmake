cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SDL3
  "Set to ON to enable the SDL3 integration"
  ON
)

if (NOT ENABLE_SDL3)
  return()
endif()

set(TEMPLATE_APP_SDL3_GIT "https://github.com/libsdl-org/SDL.git"
  CACHE STRING "The SDL3 library git source repository")
set(TEMPLATE_APP_SDL3_GIT_TAG "release-3.2.10"
  CACHE STRING "The SDL3 project git repository tag of interest")

find_package(OpenGL REQUIRED)

template_project_default_3rdparty_enabler(
  NAME SDL3
  GIT_REPOSITORY ${TEMPLATE_APP_SDL3_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL3_GIT_TAG}
)

# Normalize the consumer-facing target so dependent code can always link
# against SDL3::SDL3 regardless of whether SDL3 came in via find_package
# (which already defines the imported target) or via FetchContent's
# add_subdirectory (which exposes raw SDL3-shared / SDL3-static targets).
# if(NOT TARGET SDL3::SDL3)
#   if(TARGET SDL3-shared)
#     add_library(SDL3::SDL3 ALIAS SDL3-shared)
#   elseif(TARGET SDL3-static)
#     add_library(SDL3::SDL3 ALIAS SDL3-static)
#   elseif(TARGET SDL3)
#     add_library(SDL3::SDL3 ALIAS SDL3)
#   endif()
# endif()

if(NOT TARGET SDL3::SDL3)
  message(FATAL_ERROR
    "SDL3 enabler ran but no SDL3::SDL3 / SDL3-shared / SDL3-static "
    "target is available. Check the FetchContent build for upstream "
    "errors or install libsdl3-dev on the host.")
endif()
