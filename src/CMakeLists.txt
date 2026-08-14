cmake_minimum_required(VERSION 3.13)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})
add_link_options(${EXTRA_LINK_OPTIONS})

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

configure_file(
  project-lib-decls.h.in
  ${CMAKE_BINARY_DIR}/project-lib-decls.h
)

set(GENERAL_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks")

# The mocks which shadow a generated public header must carry the very same
# project unique include guard, otherwise both the mock and the real header
# land in the same translation unit and redefine the class.
set(GENERAL_MOCKS_BINARY_ROOT "${CMAKE_BINARY_DIR}/mocks")

configure_file(
  tests/mocks/LibraryContext/LibraryContext.h.in
  ${GENERAL_MOCKS_BINARY_ROOT}/LibraryContext/LibraryContext.h
  @ONLY
)

add_subdirectory(lib)
add_subdirectory(log)
add_subdirectory(tests)
