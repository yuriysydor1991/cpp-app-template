cmake_minimum_required(VERSION 3.22.1)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
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
  -fstack-protector-strong
  -D_FORTIFY_SOURCE=2
  -fno-common
  -fstrict-overflow
  -fstack-clash-protection
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

add_subdirectory(app)
