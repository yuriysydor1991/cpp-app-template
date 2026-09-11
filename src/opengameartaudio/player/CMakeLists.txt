cmake_minimum_required(VERSION 3.13)

# The picker reaches no audio library at all, so it stays buildable with the
# SDL2 audio enabler switched off and the player dropped.
add_library(
  TemplateProjectOpenGameArtRandomSoundObj OBJECT
  OpenGameArtRandomSound.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtRandomSoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtRandomSoundObj
)

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

add_library(
  TemplateProjectOpenGameArtSoundPlayerObj OBJECT
  OpenGameArtSdlSoundPlayer.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtSoundPlayerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOpenGameArtSoundPlayerObj
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtSoundPlayerObj
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)
