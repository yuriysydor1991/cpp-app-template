cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE Application.cpp
  PRIVATE ApplicationHelpPrinter.cpp
  PRIVATE ApplicationVersionPrinter.cpp
)

add_subdirectory(tests)
