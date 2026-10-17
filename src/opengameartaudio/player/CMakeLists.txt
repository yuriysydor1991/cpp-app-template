cmake_minimum_required(VERSION 3.13)

# The audio library free part of the subsystem, the random sound picker
# included, comes with the TemplateProjectOpenGameArtAudioObj library, so only the
# backend in use is built here.
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
