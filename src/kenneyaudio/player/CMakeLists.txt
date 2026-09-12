cmake_minimum_required(VERSION 3.13)

# The picker reaches no audio library at all, so it stays buildable with the
# SDL2 audio enabler switched off and the player dropped.
add_library(
  TemplateProjectKenneyRandomSoundObj OBJECT
  KenneyRandomSound.cpp
)

target_include_directories(
  TemplateProjectKenneyRandomSoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneyRandomSoundObj
)

# Which factory implementation is compiled is what decides the backend of the
# build, so no calling place ever branches on it with the preprocessor.
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
