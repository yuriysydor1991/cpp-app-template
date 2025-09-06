cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

install(DIRECTORY public/ DESTINATION include/${PROJECT_LIBRARY_NAME})

add_subdirectory(tests)
