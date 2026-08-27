cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectWCSLIBControllerObj OBJECT
  WCSLIBController.cpp
)

target_include_directories(
  TemplateProjectWCSLIBControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
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
  TemplateProjectWCSLIBControllerObj
)

add_subdirectory(tests)
