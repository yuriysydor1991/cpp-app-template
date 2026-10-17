cmake_minimum_required(VERSION 3.13)

# The audio library free part of the subsystem, the random sound picker
# included, comes with the TemplateProjectKenneyAudioObj library, so only the
# backend in use is built here.
if (NOT ENABLE_SDL2_AUDIO)
  add_library(
    TemplateProjectKenneySoundPlayerObj OBJECT
    KenneyNoSoundPlayerFactory.cpp
  )

  target_include_directories(
    TemplateProjectKenneySoundPlayerObj
    PRIVATE
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    TemplateProjectKenneySoundPlayerObj
  )

  return()
endif()

add_library(
  TemplateProjectKenneySoundPlayerObj OBJECT
  KenneySdlMixerSoundPlayer.cpp
  KenneySdlMixerSoundPlayerFactory.cpp
)

target_include_directories(
  TemplateProjectKenneySoundPlayerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectKenneySoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneySoundPlayerObj
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)
