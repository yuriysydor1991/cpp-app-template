cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ApplicationContext.cpp
  PRIVATE Application.cpp
  PRIVATE ApplicationFactory.cpp
  PRIVATE ApplicationHelpPrinter.cpp
  PRIVATE CommandLineParser.cpp
  PRIVATE ApplicationVersionPrinter.cpp
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${PROJECT_LIBRARY_NAME}
)

add_subdirectory(tests)
