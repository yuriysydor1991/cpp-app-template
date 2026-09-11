cmake_minimum_required(VERSION 3.13)

# The subsystem below is the very point of this branch, so it needs the sound
# categories the freesound audio enabler makes available. Turning that enabler off
# leaves nothing here to build against, hence the early and explicit stop
# instead of a missing header error later on.
if (NOT ENABLE_FREESOUND_AUDIO)
  message(
    FATAL_ERROR
    "The src/freesoundaudio subsystem needs the Freesound sound categories: either keep the ENABLE_FREESOUND_AUDIO option ON or drop the add_subdirectory(freesoundaudio) call of src/CMakeLists.txt together with the subsystem itself."
  )
endif()

add_library(
  TemplateProjectFreesoundSoundObj OBJECT
  FreesoundSound.cpp
)

target_include_directories(
  TemplateProjectFreesoundSoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundSoundObj
)

add_subdirectory(categories)
add_subdirectory(sounds)
add_subdirectory(resources)
add_subdirectory(player)
add_subdirectory(controller)
add_subdirectory(tests)
