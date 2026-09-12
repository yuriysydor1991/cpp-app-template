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

# Which factory implementation is compiled is what decides the backend of the
# build, so no calling place ever branches on it with the preprocessor.
if (NOT ENABLE_SDL2_AUDIO)
  add_library(
    TemplateProjectOpenGameArtSoundPlayerObj OBJECT
    OpenGameArtNoSoundPlayerFactory.cpp
  )

  target_include_directories(
    TemplateProjectOpenGameArtSoundPlayerObj
    PRIVATE
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    TemplateProjectOpenGameArtSoundPlayerObj
  )

  return()
endif()

add_library(
  TemplateProjectOpenGameArtSoundPlayerObj OBJECT
  OpenGameArtSdlMixerSoundPlayer.cpp
  OpenGameArtSdlMixerSoundPlayerFactory.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtSoundPlayerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOpenGameArtSoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtSoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)
