cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ApplicationContext2LibraryContext.cpp
)

add_subdirectory(tests)
