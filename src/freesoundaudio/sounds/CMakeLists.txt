cmake_minimum_required(VERSION 3.13)

# The generated index carries the sound paths of the very categories the project has
# been configured with, so the whole set is reachable from the code with no run
# time directory scanning. The freesound audio enabler writes it and points the
# FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE variable at it.
add_library(
  TemplateProjectFreesoundSoundsObj OBJECT
  FreesoundSounds.cpp
  ${FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  TemplateProjectFreesoundSoundsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundSoundsObj
)
