cmake_minimum_required(VERSION 3.13)

# The generated index carries the sound paths of the very packs the project has
# been configured with, so the whole set is reachable from the code with no run
# time directory scanning. The kenney audio enabler writes it and points the
# KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE variable at it.
add_library(
  TemplateProjectKenneySoundsObj OBJECT
  KenneySounds.cpp
  ${KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  TemplateProjectKenneySoundsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneySoundsObj
)
