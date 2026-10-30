cmake_minimum_required(VERSION 3.13)

# The subsystem below is the very point of this branch, so it needs the sound
# packs the kenney audio enabler makes available. Turning that enabler off
# leaves nothing here to build against, hence the early and explicit stop
# instead of a missing header error later on.
if (NOT ENABLE_KENNEY_AUDIO)
  message(
    FATAL_ERROR
    "The src/kenneyaudio subsystem needs the Kenney sound packs: either keep the ENABLE_KENNEY_AUDIO option ON or drop the add_subdirectory(kenneyaudio) call of src/CMakeLists.txt together with the subsystem itself."
  )
endif()

# The sources come out of the KENNEY_AUDIO_SUBSYSTEM_SOURCES list of
# src/CMakeLists.txt, the very one the app tests build, so no source is listed
# twice. The generated index carries the sound paths of the very packs the
# project has been configured with, so the whole set is reachable from the code
# with no run time directory scanning: the kenney audio enabler writes it and
# points the KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE variable at it.
add_library(
  TemplateProjectKenneyAudioObj OBJECT
  ${KENNEY_AUDIO_SUBSYSTEM_SOURCES}
  ${KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  TemplateProjectKenneyAudioObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectKenneyAudioObj
)

add_subdirectory(player)
add_subdirectory(tests)
