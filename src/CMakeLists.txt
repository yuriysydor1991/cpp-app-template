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

# The OpenGameArt audio subsystem sources, gathered before the subdirectories below
# so every test executable linking a part of it (the app ones included) builds
# the very same set.
set(
  OPENGAMEART_AUDIO_SUBSYSTEM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/OpenGameArtSound.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/packs/OpenGameArtPack.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/packs/OpenGameArtPacks.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/sounds/OpenGameArtSounds.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/resources/OpenGameArtResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/resources/OpenGameArtQtResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/resources/OpenGameArtGResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/opengameartaudio/player/OpenGameArtRandomSound.cpp
)

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(opengameartaudio)

if (ENABLE_SDL2_AUDIO)
  target_compile_definitions(${PROJECT_BINARY_NAME} PRIVATE TEMPLATE_APP_SDL2_AUDIO=1)
endif()
