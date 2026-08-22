cmake_minimum_required(VERSION 3.13)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})
add_link_options(${EXTRA_LINK_OPTIONS})

add_executable(
  ${PROJECT_BINARY_NAME}
  main.cpp
)

target_include_directories(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

install(
  TARGETS ${PROJECT_BINARY_NAME}
  RUNTIME DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

# The Font Awesome subsystem sources, gathered before the subdirectories below
# so every test executable linking a part of it (the app ones included) builds
# the very same set.
set(
  FONTAWESOME_STYLES_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/styles/FontAwesomeSolidStyle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/styles/FontAwesomeRegularStyle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/styles/FontAwesomeBrandsStyle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/styles/FontAwesomeStyles.cpp
)

set(
  FONTAWESOME_SUBSYSTEM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/FontAwesomeIcon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/icons/FontAwesomeIcons.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/resources/FontAwesomeResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/resources/FontAwesomeQtResourcePath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fontawesome/resources/FontAwesomeGResourcePath.cpp
  ${FONTAWESOME_STYLES_SOURCES}
)

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(fontawesome)
