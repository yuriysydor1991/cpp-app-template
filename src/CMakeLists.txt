cmake_minimum_required(VERSION 3.13)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

set(GENERAL_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks")

add_subdirectory(lib)
add_subdirectory(log)
