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
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

install(
  TARGETS ${PROJECT_BINARY_NAME}
  RUNTIME DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

# The installed executable finds the project library through a RUNPATH relative
# to its own location, whatever the prefix and the library directory (lib,
# lib64 or lib/<multiarch>) of the installation are.
if(UNIX)
  get_filename_component(
    binInstallDir ${PROJECT_BINARY_INSTALLATION_DIR}
    ABSOLUTE BASE_DIR ${CMAKE_INSTALL_PREFIX}
  )
  file(RELATIVE_PATH bin2LibDir ${binInstallDir} ${CMAKE_INSTALL_FULL_LIBDIR})

  if(APPLE)
    set(binOriginDir "@loader_path")
  else()
    set(binOriginDir "$ORIGIN")
  endif()

  set_target_properties(
    ${PROJECT_BINARY_NAME}
    PROPERTIES INSTALL_RPATH "${binOriginDir}/${bin2LibDir}"
  )
endif()

configure_file(
  project-global-decls.h.in
  ${PROJECT_BINARY_DIR}/project-global-decls.h
)

set(GENERAL_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks")

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(converters)
add_subdirectory(lib)
