cmake_minimum_required(VERSION 3.22.1)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})

add_executable(
  ${PROJECT_NAME}
  main.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
)

execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
        OUTPUT_VARIABLE PROJECT_GIT_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

add_subdirectory(app)
