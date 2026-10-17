cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SDL2
  "Set to ON to enable the SDL2 integration"
  ON
)

if (NOT ENABLE_SDL2)
  return()
endif()

set(TEMPLATE_APP_SDL2_GIT "https://github.com/libsdl-org/SDL.git" CACHE STRING "The SDL2 library git source repository")
set(TEMPLATE_APP_SDL2_GIT_TAG "release-2.32.10" CACHE STRING "The SDL2 project git repository tag of interest")

find_package(OpenGL REQUIRED)

# the project installs no SDL2 build of its own (SDL2_DISABLE_INSTALL is ON for a subproject),
# so the downloaded SDL2 links statically into the binary
set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the downloaded SDL2 library")
set(SDL_STATIC ON CACHE BOOL "Build a static version of the downloaded SDL2 library")

template_project_default_3rdparty_enabler(
  NAME SDL2
  GIT_REPOSITORY ${TEMPLATE_APP_SDL2_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL2_GIT_TAG}
)

if(NOT TARGET SDL2::SDL2)
  message(FATAL_ERROR
    "SDL2 enabler ran but no SDL2::SDL2 / SDL2 / SDL2-static target is "
    "available. Check the FetchContent build for upstream errors or "
    "install libsdl2-dev on the host.")
endif()
