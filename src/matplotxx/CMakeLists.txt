cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_MATPLOTCXX)
  message(
    FATAL_ERROR
    "The src/matplotxx sources require the Matplot++ library which is turned "
    "off by the ENABLE_MATPLOTCXX=OFF parameter. Drop the "
    "add_subdirectory(matplotxx) call from the src/CMakeLists.txt file "
    "together with the whole src/matplotxx subdirectory and the Matplot++ "
    "example of the src/app/applications/Application.cpp file to build the "
    "project without the Matplot++ library."
  )
endif()

add_library(
  TemplateProjectMatPlotxxControllerObj OBJECT
  MatPlotxxController.cpp
)

target_include_directories(
  TemplateProjectMatPlotxxControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectMatPlotxxControllerObj
  Matplot++::matplot
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectMatPlotxxControllerObj
  Matplot++::matplot
)

add_subdirectory(tests)
