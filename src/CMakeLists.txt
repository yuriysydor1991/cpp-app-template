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

# The Freesound audio subsystem sources, gathered before the subdirectories below
# so every test executable linking a part of it (the app ones included) builds
# the very same set.
set(
  FREESOUND_AUDIO_SUBSYSTEM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/FreesoundSound.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/categories/FreesoundCategories.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/sounds/FreesoundSounds.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/resources/FreesoundResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/resources/FreesoundQtResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/resources/FreesoundGResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/freesoundaudio/player/FreesoundRandomSound.cpp
)

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(freesoundaudio)

if (ENABLE_SDL2_AUDIO)
  target_compile_definitions(${PROJECT_BINARY_NAME} PRIVATE TEMPLATE_APP_SDL2_AUDIO=1)
endif()
