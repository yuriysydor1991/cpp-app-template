cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE SignalsHandler.cpp
)

add_subdirectory(handlers)
add_subdirectory(tests)
