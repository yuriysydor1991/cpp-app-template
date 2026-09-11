cmake_minimum_required(VERSION 3.13)

# The generated index carries the sound paths of the very packs the project has
# been configured with, so the whole set is reachable from the code with no run
# time directory scanning. The opengameart audio enabler writes it and points the
# OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE variable at it.
add_library(
  TemplateProjectOpenGameArtSoundsObj OBJECT
  OpenGameArtSounds.cpp
  ${OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  TemplateProjectOpenGameArtSoundsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtSoundsObj
)
