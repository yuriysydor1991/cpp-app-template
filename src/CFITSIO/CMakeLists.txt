cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectCFITSIOControllerObj OBJECT
  CFITSIOController.cpp
)

target_include_directories(
  TemplateProjectCFITSIOControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The CFITSIO itself is made available by the CFITSIO enabler. The PUBLIC
# keyword hands its headers over to the sources above and its library over to
# the executable which links this object library.
target_link_libraries(
  TemplateProjectCFITSIOControllerObj
  PUBLIC CFITSIO::cfitsio
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectCFITSIOControllerObj
)

add_subdirectory(tests)
