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

# The public LibraryFacade.h declares the logger instance adoption, so the
# logging interface is a public header too. It keeps living in the src/log
# subsystem directory, which the whole template branch family shares, and is
# copied next to the facade headers instead of being moved: only the install
# rule and the LibraryFacade.h include make it public. Unlike the facade
# headers it is not configured, because it carries no project unique namespace
# on purpose - see the logger::ILogger documentation. The severity constants
# come along, because the interface LVL_* values are defined through them.
set(PROJECT_LIB_PUBLIC_LOG_HEADERS ILogger.h severity-macro-consts.h)

foreach(header ${PROJECT_LIB_PUBLIC_LOG_HEADERS})
  configure_file(
    ${CMAKE_SOURCE_DIR}/src/log/${header}
    ${PROJECT_LIB_PUBLIC_INCLUDE_DIR}/${PROJECT_LIBRARY_NAME}/${header}
    COPYONLY
  )
endforeach()

# The headers are generated unconditionally, because the library itself is
# built against them. Only their installation is a development files matter.
if(LIB_INSTALL_DEV_FILES)
  install(
    DIRECTORY ${PROJECT_LIB_PUBLIC_INCLUDE_DIR}/${PROJECT_LIBRARY_NAME}
    DESTINATION include
  )
endif()

add_subdirectory(tests)
