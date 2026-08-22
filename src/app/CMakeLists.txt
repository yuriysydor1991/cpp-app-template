cmake_minimum_required(VERSION 3.13)

set(APP_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks")
set(APPLICATIONS_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/applications/tests/mocks")

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ApplicationContext.cpp
  PRIVATE ApplicationFactory.cpp
  PRIVATE CommandLineParser.cpp
)

add_subdirectory(applications)
add_subdirectory(tests)
