cmake_minimum_required(VERSION 3.13)

# The subsystem below is the very point of this branch, so it needs the icon
# set the fontawesome enabler makes available. Turning that enabler off leaves
# nothing here to build against, hence the early and explicit stop instead of a
# missing header error later on.
if (NOT ENABLE_FONTAWESOME)
  message(
    FATAL_ERROR
    "The src/fontawesome subsystem needs the Font Awesome icon set: either keep the ENABLE_FONTAWESOME option ON or drop the add_subdirectory(fontawesome) call of src/CMakeLists.txt together with the subsystem itself."
  )
endif()

# The sources come out of the FONTAWESOME_SUBSYSTEM_SOURCES list of
# src/CMakeLists.txt, the very one the app tests build, so no source is listed
# twice. The generated index carries the names of every icon of the very Font
# Awesome checkout the project has been configured with, so the whole set is
# reachable from the code with no run time directory scanning: the fontawesome
# enabler writes it and points the FONTAWESOME_GENERATED_ICONS_SOURCE variable
# at it.
add_library(
  TemplateProjectFontAwesomeObj OBJECT
  ${FONTAWESOME_SUBSYSTEM_SOURCES}
  ${FONTAWESOME_GENERATED_ICONS_SOURCE}
)

target_include_directories(
  TemplateProjectFontAwesomeObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectFontAwesomeObj
)

add_subdirectory(tests)
