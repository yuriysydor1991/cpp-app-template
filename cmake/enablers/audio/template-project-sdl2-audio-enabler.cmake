cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SDL2_AUDIO
  "Set to ON to capture the default microphone of this branch through the SDL2 audio subsystem"
  ON
)

set(TEMPLATE_APP_SDL2_GIT "https://github.com/libsdl-org/SDL.git" CACHE STRING "The SDL2 library git source repository")
set(TEMPLATE_APP_SDL2_GIT_TAG "release-2.32.10" CACHE STRING "The SDL2 project git repository tag of interest")

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

# The whisper.cpp examples capture the microphone through the very same
# library, and it's audio subsystem is the only part of it taken here: no
# window, no renderer and no OpenGL.
template_project_default_3rdparty_enabler(
  NAME SDL2
  GIT_REPOSITORY ${TEMPLATE_APP_SDL2_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL2_GIT_TAG}
)

foreach(sdlTarget IN ITEMS SDL2::SDL2 SDL2::SDL2-static SDL2)
  if (TARGET ${sdlTarget})
    set(TEMPLATE_APP_SDL2_AUDIO_TARGET ${sdlTarget})
    break()
  endif()
endforeach()

if (NOT TEMPLATE_APP_SDL2_AUDIO_TARGET)
  message(
    FATAL_ERROR
    "The SDL2 audio enabler ran but no SDL2::SDL2, SDL2::SDL2-static or SDL2 target is available. Install libsdl2-dev on the host or check the FetchContent build for upstream errors."
  )
endif()

message(STATUS "The microphone capture links against: ${TEMPLATE_APP_SDL2_AUDIO_TARGET}")

# The FetchContent built SDL2 is the 3rd-party code as much as the installed
# one, so it's headers stay out of the project warnings and the clang-tidy
# checks.
get_target_property(sdlAliasedTarget ${TEMPLATE_APP_SDL2_AUDIO_TARGET} ALIASED_TARGET)

if (sdlAliasedTarget)
  set_target_properties(${sdlAliasedTarget} PROPERTIES SYSTEM ON)
else()
  set_target_properties(${TEMPLATE_APP_SDL2_AUDIO_TARGET} PROPERTIES SYSTEM ON)
endif()

# Link the ${TEMPLATE_APP_SDL2_AUDIO_TARGET} target to your target(s) of
# interest (e.g. the ${PROJECT_BINARY_NAME} executable or any of your own
# libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} ${TEMPLATE_APP_SDL2_AUDIO_TARGET})
