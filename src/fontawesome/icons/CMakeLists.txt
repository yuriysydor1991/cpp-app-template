cmake_minimum_required(VERSION 3.13)

# The generated index carries the names of every icon of the very Font Awesome
# checkout the project has been configured with, so the whole set is reachable
# from the code with no run time directory scanning. The fontawesome enabler
# writes it and points the FONTAWESOME_GENERATED_ICONS_SOURCE variable at it.
add_library(
  TemplateProjectFontAwesomeIconsObj OBJECT
  FontAwesomeIcons.cpp
  ${FONTAWESOME_GENERATED_ICONS_SOURCE}
)

target_include_directories(
  TemplateProjectFontAwesomeIconsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFontAwesomeIconsObj
)
