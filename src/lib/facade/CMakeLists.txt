cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

install(
  FILES 
    LibraryFacade.h 
    LibraryContext.h
    ILib.h
  DESTINATION include/${PROJECT_LIBRARY_NAME} 
  COMPONENT Development
)

add_subdirectory(tests)
