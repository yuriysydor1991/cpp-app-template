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

add_library(
  TemplateProjectOpenGameArtSoundObj OBJECT
  OpenGameArtSound.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtSoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtSoundObj
)

add_subdirectory(packs)
add_subdirectory(sounds)
add_subdirectory(resources)
add_subdirectory(player)
add_subdirectory(tests)
