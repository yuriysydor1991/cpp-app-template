cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_WCSLIB)
  message(
    FATAL_ERROR
    "The src/WCSLIB sources require the WCSLIB library which is turned off by "
    "the ENABLE_WCSLIB=OFF parameter. Drop the add_subdirectory(WCSLIB) call from the "
    "src/CMakeLists.txt file together with the whole src/WCSLIB subdirectory "
    "and the WCSLIB usage of the src/app/applications/Application.cpp file to "
    "build the project without the WCSLIB library."
  )
endif()

add_library(
  TemplateProjectWCSLIBControllerObj OBJECT
  WCSLIBController.cpp
)

target_include_directories(
  TemplateProjectWCSLIBControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The WCSLIB itself is made available by the WCSLIB enabler. The PUBLIC keyword
# hands its library over to the executable which links this object library,
# while its headers stay private: the WCSLIBController.h declares no WCSLIB
# type of its own.
target_link_libraries(
  TemplateProjectWCSLIBControllerObj
  PUBLIC WCSLIB::wcslib
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectWCSLIBControllerObj
)

add_subdirectory(tests)
