cmake_minimum_required(VERSION 3.13)

# The subsystem below is the very point of this branch, so it needs the sound
# packs the opengameart audio enabler makes available. Turning that enabler off
# leaves nothing here to build against, hence the early and explicit stop
# instead of a missing header error later on.
if (NOT ENABLE_OPENGAMEART_AUDIO)
  message(
    FATAL_ERROR
    "The src/opengameartaudio subsystem needs the OpenGameArt sound packs: either keep the ENABLE_OPENGAMEART_AUDIO option ON or drop the add_subdirectory(opengameartaudio) call of src/CMakeLists.txt together with the subsystem itself."
  )
endif()

# The sources come out of the OPENGAMEART_AUDIO_SUBSYSTEM_SOURCES list of
# src/CMakeLists.txt, the very one the app tests build, so no source is listed
# twice. The generated index carries the sound paths the project has been
# configured with, so the whole set is reachable from the code with no run time
# directory scanning: the enabler writes it and points the
# OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE variable at it.
add_library(
  TemplateProjectOpenGameArtAudioObj OBJECT
  ${OPENGAMEART_AUDIO_SUBSYSTEM_SOURCES}
  ${OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  TemplateProjectOpenGameArtAudioObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectOpenGameArtAudioObj
)

add_subdirectory(player)
add_subdirectory(tests)
