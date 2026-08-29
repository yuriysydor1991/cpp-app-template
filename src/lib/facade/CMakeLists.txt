cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

# The logging interface the public LibraryFacade.h accepts lives among the
# public headers, so the whole installable surface is one directory and nothing
# outside of it is ever installed.
if(LIB_INSTALL_DEV_FILES)
  install(DIRECTORY public/ DESTINATION include/${PROJECT_LIBRARY_NAME})
endif()

add_subdirectory(tests)
