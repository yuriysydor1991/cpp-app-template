cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SDL2_AUDIO
  "Set to ON to build the sound player of this branch against the SDL2 audio subsystem"
  ON
)

set(TEMPLATE_APP_SDL2_GIT "https://github.com/libsdl-org/SDL.git" CACHE STRING "The SDL2 library git source repository")
set(TEMPLATE_APP_SDL2_GIT_TAG "release-2.32.10" CACHE STRING "The SDL2 project git repository tag of interest")

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

# The sound categories are the point of this branch and the player is the
# smallest thing able to prove they really sound, so the audio subsystem of
# SDL2 is taken and nothing else of it: no window, no renderer and no OpenGL.
template_project_default_3rdparty_enabler(
  NAME SDL2
  GIT_REPOSITORY ${TEMPLATE_APP_SDL2_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL2_GIT_TAG}
)

if (TARGET SDL2::SDL2)
  set(TEMPLATE_APP_SDL2_AUDIO_TARGET SDL2::SDL2 CACHE INTERNAL "The SDL2 target the sound player links against")
elseif (TARGET SDL2::SDL2-static)
  set(TEMPLATE_APP_SDL2_AUDIO_TARGET SDL2::SDL2-static CACHE INTERNAL "The SDL2 target the sound player links against")
elseif (TARGET SDL2)
  set(TEMPLATE_APP_SDL2_AUDIO_TARGET SDL2 CACHE INTERNAL "The SDL2 target the sound player links against")
else()
  message(
    FATAL_ERROR
    "The SDL2 audio enabler ran but no SDL2::SDL2, SDL2::SDL2-static or SDL2 target is available. Install libsdl2-dev on the host, check the FetchContent build for upstream errors, or switch the ENABLE_SDL2_AUDIO option OFF to drop the sound player."
  )
endif()

message(STATUS "The sound player links against: ${TEMPLATE_APP_SDL2_AUDIO_TARGET}")
