cmake_minimum_required(VERSION 3.13)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})
add_link_options(${EXTRA_LINK_OPTIONS})

add_executable(
  ${PROJECT_BINARY_NAME}
  main.cpp
)

target_include_directories(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

install(
  TARGETS ${PROJECT_BINARY_NAME}
  RUNTIME DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

# The Kenney audio subsystem sources, gathered before the subdirectories below
# so every test executable linking a part of it (the app ones included) builds
# the very same set.
# The backend free factory the app tests take, so they exercise the demo with
# no audio library linked at all.
set(
  KENNEY_AUDIO_NO_PLAYER_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/player/KenneyNoSoundPlayerFactory.cpp
)

set(
  KENNEY_AUDIO_SUBSYSTEM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/KenneySound.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/packs/KenneyPack.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/packs/KenneyPacks.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/sounds/KenneySounds.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/resources/KenneyResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/resources/KenneyQtResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/resources/KenneyGResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/player/KenneyRandomSound.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/kenneyaudio/controller/KenneySoundsController.cpp
)

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(kenneyaudio)

