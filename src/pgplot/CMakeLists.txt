cmake_minimum_required(VERSION 3.13)

if (NOT TARGET PGPLOT::cpgplot)
  message(
    FATAL_ERROR
    "The src/pgplot sources require the PGPLOT integration which is turned off "
    "by the ENABLE_PGPLOT=OFF parameter. Drop the add_subdirectory(pgplot) call "
    "from the src/CMakeLists.txt file together with the whole src/pgplot "
    "subdirectory to build the project without the PGPLOT library."
  )
endif()

add_library(
  TemplateProjectPGPLOTControllerObj OBJECT
  PGPLOTController.cpp
)

target_include_directories(
  TemplateProjectPGPLOTControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectPGPLOTControllerObj
  PGPLOT::cpgplot
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectPGPLOTControllerObj
  PGPLOT::cpgplot
)
