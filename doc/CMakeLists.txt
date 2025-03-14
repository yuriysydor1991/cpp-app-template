cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_DOC_DOXYGEN)
  return()
endif()

find_package(Doxygen REQUIRED)

set(DOXYGEN_IN Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

if (DOXYGEN_OUTPUT_LANGUAGE STREQUAL "Ukrainian")
  set(DOXYGEN_MAIN_PAGE_MD "doc/README.uk_UA.md")
endif()

configure_file(
  ${DOXYGEN_IN} 
  ${DOXYGEN_OUT}
)

add_custom_target(
  Doxygen-doc
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Generating project documentation with Doxygen"
  VERBATIM
)

if(DOXYGEN_DO_INSTALL)
  message(STATUS "Doxygen html doc install enabled for the ${DOXYGEN_OUT_HTML} directory")

  install(
    DIRECTORY ${DOXYGEN_OUT_HTML}
    DESTINATION share/docs
    COMPONENT Documentation
  )
endif()
