cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_CFITSIO)
  message(
    FATAL_ERROR
    "The src/CFITSIO sources require the CFITSIO library which is turned off by "
    "the ENABLE_CFITSIO=OFF parameter. Drop the add_subdirectory(CFITSIO) call from the "
    "src/CMakeLists.txt file together with the whole src/CFITSIO subdirectory "
    "and the CFITSIO usage of the src/app/applications/Application.cpp file to "
    "build the project without the CFITSIO library."
  )
endif()

add_library(
  TemplateProjectCFITSIOControllerObj OBJECT
  CFITSIOContext.cpp
  CFITSIOController.cpp
)

target_include_directories(
  TemplateProjectCFITSIOControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
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
  PRIVATE TemplateProjectCFITSIOControllerObj
)

add_subdirectory(tests)
