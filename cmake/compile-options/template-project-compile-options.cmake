cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/compile-options")

# CMAKE_C_COMPILER_ID STREQUAL "Clang"
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  include(template-project-compile-options-MSVC)
else()
  include(template-project-compile-options-GCC)
endif()

set(
  EXTRA_COMPILE_OPTIONS 
  ${EXTRA_COMPILE_OPTIONS} 
  -DMAX_LOG_LEVEL=${MAX_LOG_LEVEL}
  -DDEFAULT_LOG_FILE_PATH="${DEFAULT_LOG_FILE_PATH}"
)

message(STATUS "COMPILER ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "COMPILE OPTIONS: ${EXTRA_COMPILE_OPTIONS}")
