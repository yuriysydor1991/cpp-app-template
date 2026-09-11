cmake_minimum_required(VERSION 3.13)

# The picker reaches no audio library at all, so it stays buildable with the
# SDL2 audio enabler switched off and the player dropped.
add_library(
  TemplateProjectFreesoundRandomSoundObj OBJECT
  FreesoundRandomSound.cpp
)

target_include_directories(
  TemplateProjectFreesoundRandomSoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundRandomSoundObj
)

# Which factory implementation is compiled is what decides the backend of the
# build, so no calling place ever branches on it with the preprocessor.
if (NOT ENABLE_SDL2_AUDIO)
  add_library(
    TemplateProjectFreesoundSoundPlayerObj OBJECT
    FreesoundNoSoundPlayerFactory.cpp
  )

  target_include_directories(
    TemplateProjectFreesoundSoundPlayerObj
    PRIVATE
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
  )

  target_link_libraries(
    ${PROJECT_BINARY_NAME}
    TemplateProjectFreesoundSoundPlayerObj
  )

  return()
endif()

add_library(
  TemplateProjectFreesoundSoundPlayerObj OBJECT
  FreesoundSdlSoundPlayer.cpp
  FreesoundSdlSoundPlayerFactory.cpp
)

target_include_directories(
  TemplateProjectFreesoundSoundPlayerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectFreesoundSoundPlayerObj
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundSoundPlayerObj
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)
