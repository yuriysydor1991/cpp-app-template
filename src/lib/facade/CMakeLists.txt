cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE LibraryFacade.cpp
)

if(LIB_INSTALL_DEV_FILES)
  install(DIRECTORY public/ DESTINATION include/${PROJECT_LIBRARY_NAME})

  # The logging interface is referenced by the public LibraryFacade.h header, so
  # it is installed next to it and not under its src/log build tree path.
  install(
    FILES
      ${CMAKE_SOURCE_DIR}/src/log/ILogger.h
      ${CMAKE_SOURCE_DIR}/src/log/severity-macro-consts.h
    DESTINATION include/${PROJECT_LIBRARY_NAME}
  )
endif()

add_subdirectory(tests)
