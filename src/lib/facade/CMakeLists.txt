cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

# The public headers carry the project unique library namespace and include
# guards, so each of them is generated into the library own include
# subdirectory instead of being installed as is. The library user includes them
# as <library name>/<header name>, so the identically named headers of the
# different derived libraries never shadow each other.
set(PROJECT_LIB_PUBLIC_HEADERS ILib.h LibraryContext.h LibraryFacade.h)

foreach(header ${PROJECT_LIB_PUBLIC_HEADERS})
  configure_file(
    public/${header}.in
    ${PROJECT_LIB_PUBLIC_INCLUDE_DIR}/${PROJECT_LIBRARY_NAME}/${header}
    @ONLY
  )
endforeach()

install(
  DIRECTORY ${PROJECT_LIB_PUBLIC_INCLUDE_DIR}/${PROJECT_LIBRARY_NAME}
  DESTINATION include
)

add_subdirectory(tests)
