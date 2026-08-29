cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

# The public headers are installed into the library own include subdirectory,
# so the library user includes them as <library name>/<header name> and the
# identically named headers of the different derived libraries never shadow
# each other.
#
# The public LibraryFacade.h declares the logger instance adoption, so the
# logging interface is a public header too. It keeps living in the src/log
# subsystem directory, which the whole template branch family shares, and is
# installed from there instead of being moved: only the install rule and the
# LibraryFacade.h include make it public. Unlike the facade headers it carries
# no version carrying library namespace on purpose - see the logger::ILogger
# documentation. The severity constants come along, because the interface LVL_*
# values are defined through them.
if(LIB_INSTALL_DEV_FILES)
  install(
    DIRECTORY public/
    DESTINATION include/${PROJECT_LIBRARY_NAME}
    COMPONENT Development
  )

  install(
    FILES
      ${CMAKE_SOURCE_DIR}/src/log/ILogger.h
      ${CMAKE_SOURCE_DIR}/src/log/severity-macro-consts.h
    DESTINATION include/${PROJECT_LIBRARY_NAME}
    COMPONENT Development
  )
endif()

add_subdirectory(tests)
