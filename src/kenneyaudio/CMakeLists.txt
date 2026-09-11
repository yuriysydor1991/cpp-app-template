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

add_library(
  TemplateProjectKenneySoundObj OBJECT
  KenneySound.cpp
)

target_include_directories(
  TemplateProjectKenneySoundObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneySoundObj
)

add_subdirectory(packs)
add_subdirectory(sounds)
add_subdirectory(resources)
add_subdirectory(player)
add_subdirectory(controller)
add_subdirectory(tests)
