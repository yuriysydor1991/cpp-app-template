cmake_minimum_required(VERSION 3.13)

find_program(GRSC_EXEC glib-compile-resources)

configure_file(template.gresource.xml.in template.gresource.xml)

set(RESOURCE_XML "${CMAKE_CURRENT_BINARY_DIR}/template.gresource.xml")
set(RESOURCE_C "${CMAKE_CURRENT_BINARY_DIR}/template-resources.c")

# Every listed resource file is a dependency of the generated source, so an
# edited resource is compiled into the binary again on the next build.
execute_process(
  COMMAND ${GRSC_EXEC} --generate-dependencies
          --sourcedir=${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCE_XML}
  OUTPUT_VARIABLE RESOURCE_FILES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REPLACE "\n" ";" RESOURCE_FILES "${RESOURCE_FILES}")

add_custom_command(
  OUTPUT ${RESOURCE_C}
  COMMAND ${GRSC_EXEC}
          --target=${RESOURCE_C}
          --generate-source
          ${RESOURCE_XML}
  DEPENDS ${RESOURCE_XML} ${RESOURCE_FILES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Generating GResource source for ${PROJECT_NAME} (cleaned compile options WITH NO -Wall -Wextra)"
)

add_library(
  gresourcelib OBJECT
  ${RESOURCE_C}
)

set_target_properties(gresourcelib PROPERTIES COMPILE_OPTIONS "")

target_include_directories(
  gresourcelib
  PRIVATE 
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  gresourcelib
)
