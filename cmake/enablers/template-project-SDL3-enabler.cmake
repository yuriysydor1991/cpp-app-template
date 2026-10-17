cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SDL3
  "Set to ON to enable the SDL3 integration"
  ON
)

if (NOT ENABLE_SDL3)
  return()
endif()

set(TEMPLATE_APP_SDL3_GIT "https://github.com/libsdl-org/SDL.git" CACHE STRING "The SDL3 library git source repository")
set(TEMPLATE_APP_SDL3_GIT_TAG "release-3.2.10" CACHE STRING "The SDL3 project git repository tag of interest")

find_package(OpenGL REQUIRED)

# the project installs no SDL3 build of its own (SDL_INSTALL is OFF for a subproject),
# so the downloaded SDL3 links statically into the binary
set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the downloaded SDL3 library")
set(SDL_STATIC ON CACHE BOOL "Build a static version of the downloaded SDL3 library")

template_project_default_3rdparty_enabler(
  NAME SDL3
  GIT_REPOSITORY ${TEMPLATE_APP_SDL3_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL3_GIT_TAG}
)

if(NOT TARGET SDL3::SDL3)
  message(FATAL_ERROR
    "SDL3 enabler ran but no SDL3::SDL3 / SDL3-shared / SDL3-static "
    "target is available. Check the FetchContent build for upstream "
    "errors or install libsdl3-dev on the host.")
endif()
