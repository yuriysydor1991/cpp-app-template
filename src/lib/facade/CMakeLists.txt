cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

# The public headers are installed into the library own include subdirectory,
# so the library user includes them as <library name>/<header name> and the
# identically named headers of the different derived libraries never shadow
# each other. The logging interface the public LibraryFacade.h accepts lives
# among them, so the whole installable surface is one directory and nothing
# outside of it is ever installed.
if(LIB_INSTALL_DEV_FILES)
  install(
    DIRECTORY public/
    DESTINATION include/${PROJECT_LIBRARY_NAME}
    COMPONENT Development
  )
endif()

add_subdirectory(tests)
