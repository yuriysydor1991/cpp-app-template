cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ASignalsHandler.cpp
)

add_subdirectory(posix)
add_subdirectory(tests)
