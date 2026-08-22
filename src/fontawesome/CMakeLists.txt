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

add_library(
  TemplateProjectFontAwesomeIconObj OBJECT
  FontAwesomeIcon.cpp
)

target_include_directories(
  TemplateProjectFontAwesomeIconObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFontAwesomeIconObj
)

add_subdirectory(styles)
add_subdirectory(icons)
add_subdirectory(resources)
add_subdirectory(tests)
