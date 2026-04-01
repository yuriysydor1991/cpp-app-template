cmake_minimum_required(VERSION 3.13)

find_package(Matplot++ REQUIRED)

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
  ${PROJECT_BINARY_NAME}
  TemplateProjectMatPlotxxControllerObj
  Matplot++::matplot
)
