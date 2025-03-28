cmake_minimum_required(VERSION 3.13)

# CMAKE_C_COMPILER_ID STREQUAL "Clang"
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  include(template-project-compile-options-MSVC)
else()
  include(template-project-compile-options-GCC)
endif()

message(STATUS "COMPILER ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "COMPILE OPTIONS: ${EXTRA_COMPILE_OPTIONS}")
