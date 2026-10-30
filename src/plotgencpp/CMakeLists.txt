cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectPlotGenCppControllerObj OBJECT
  PlotGenCppController.cpp
)

target_include_directories(
  TemplateProjectPlotGenCppControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectPlotGenCppControllerObj
)

add_subdirectory(tests)
