cmake_minimum_required(VERSION 3.13)

find_package(plplot REQUIRED COMPONENTS CXX)

add_library(
  TemplateProjectPLPlotControllerObj OBJECT
  PLplotController.cpp
)

target_include_directories(
  TemplateProjectPLPlotControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectPLPlotControllerObj
  PLPLOT::plplot
  PLPLOT::plplotcxx
)
