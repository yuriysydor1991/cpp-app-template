cmake_minimum_required(VERSION 3.22.1)

#-D_FORTIFY_SOURCE=2 (needs OPT); -Werror (causes some stdlib errors)
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -Wimplicit-fallthrough
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wuseless-cast
  -Wmisleading-indentation
  -Wzero-as-null-pointer-constant
  -fanalyzer
  -fstack-protector-all
  -fno-common
  -fstrict-overflow
  -pie
  -Wl,-z,relro
  -Wl,-z,now
)

add_executable(
  ${PROJECT_NAME}
  main.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
)

find_package(Git REQUIRED)
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
