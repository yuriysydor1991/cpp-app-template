cmake_minimum_required(VERSION 3.13)

# The audio library free part of the subsystem, the random sound picker
# included, comes with the TemplateProjectFreesoundAudioObj library, so only the
# backend in use is built here.
if (NOT ENABLE_SDL2_AUDIO)
  add_library(
    TemplateProjectFreesoundSoundPlayerObj OBJECT
    FreesoundNoSoundPlayerFactory.cpp
  )

  target_include_directories(
    TemplateProjectFreesoundSoundPlayerObj
    PRIVATE
      ${PROJECT_SOURCE_DIR}
      ${PROJECT_BINARY_DIR}
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    PRIVATE TemplateProjectFreesoundSoundPlayerObj
  )

  return()
endif()

add_library(
  TemplateProjectFreesoundSoundPlayerObj OBJECT
  FreesoundSdlMixerSoundPlayer.cpp
  FreesoundSdlMixerSoundPlayerFactory.cpp
)

target_include_directories(
  TemplateProjectFreesoundSoundPlayerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectFreesoundSoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectFreesoundSoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)
