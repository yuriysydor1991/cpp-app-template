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

set(TEMPLATE_APP_SDL2_MIXER_GIT "https://github.com/libsdl-org/SDL_mixer.git" CACHE STRING "The SDL_mixer library git source repository")
set(TEMPLATE_APP_SDL2_MIXER_GIT_TAG "release-2.8.1" CACHE STRING "The SDL_mixer project git repository tag of interest")

# SDL2 itself decodes the RIFF/WAVE files alone, while the sounds Freesound
# serves anonymously are the .ogg previews, so the decoders of the SDL_mixer
# satellite library are what makes them audible at all.
#
# Only the decoders SDL_mixer carries inside it's own sources are taken - the
# stb_vorbis .ogg one, the minimp3 .mp3 one and the drflac .flac one - so a
# FetchContent build asks for no third party library of it's own. The rest
# needs one installed on the host (opusfile, libxmp, FluidSynth, WavPack) and
# is switched off here instead of failing the configure of a host carrying
# none.
set(SDL2MIXER_VORBIS "STB" CACHE STRING "The SDL_mixer .ogg decoder: the built in stb_vorbis one")
set(SDL2MIXER_OPUS OFF CACHE BOOL "Build the SDL_mixer Opus decoder, which needs the system opusfile library")
set(SDL2MIXER_MOD OFF CACHE BOOL "Build the SDL_mixer MOD decoders, which need the system libxmp or modplug library")
set(SDL2MIXER_MIDI OFF CACHE BOOL "Build the SDL_mixer MIDI outputs, the FluidSynth one needing the system library")
set(SDL2MIXER_WAVPACK OFF CACHE BOOL "Build the SDL_mixer WavPack decoder, which needs the system wavpack library")

template_project_default_3rdparty_enabler(
  NAME SDL2_mixer
  GIT_REPOSITORY ${TEMPLATE_APP_SDL2_MIXER_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDL2_MIXER_GIT_TAG}
)

if (TARGET SDL2_mixer::SDL2_mixer)
  set(TEMPLATE_APP_SDL2_MIXER_TARGET SDL2_mixer::SDL2_mixer CACHE INTERNAL "The SDL_mixer target the sound player links against")
elseif (TARGET SDL2_mixer::SDL2_mixer-static)
  set(TEMPLATE_APP_SDL2_MIXER_TARGET SDL2_mixer::SDL2_mixer-static CACHE INTERNAL "The SDL_mixer target the sound player links against")
elseif (TARGET SDL2_mixer)
  set(TEMPLATE_APP_SDL2_MIXER_TARGET SDL2_mixer CACHE INTERNAL "The SDL_mixer target the sound player links against")
else()
  message(
    FATAL_ERROR
    "The SDL2 audio enabler ran but no SDL2_mixer::SDL2_mixer, SDL2_mixer::SDL2_mixer-static or SDL2_mixer target is available. Install libsdl2-mixer-dev on the host, check the FetchContent build for upstream errors, or switch the ENABLE_SDL2_AUDIO option OFF to drop the sound player."
  )
endif()

message(STATUS "The sound player decodes with: ${TEMPLATE_APP_SDL2_MIXER_TARGET}")
