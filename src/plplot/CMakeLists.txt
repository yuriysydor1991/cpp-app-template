cmake_minimum_required(VERSION 3.13)

# The option itself is declared by the enabler only after the src directory.
if (DEFINED ENABLE_PLPLOT AND NOT ENABLE_PLPLOT)
  message(
    FATAL_ERROR
    "The src/plplot sources require the PLplot library which is turned off by "
    "the ENABLE_PLPLOT=OFF parameter. Drop the add_subdirectory(plplot) call "
    "from the src/CMakeLists.txt file together with the whole src/plplot "
    "subdirectory and the PLplot example of the "
    "src/app/applications/Application.cpp file to build the project without "
    "the PLplot library."
  )
endif()

add_library(
  TemplateProjectPLPlotControllerObj OBJECT
  PLplotController.cpp
  PLplotDevicePicker.cpp
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
)

add_subdirectory(tests)
