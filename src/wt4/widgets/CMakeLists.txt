cmake_minimum_required(VERSION 3.13)

find_package(Wt REQUIRED COMPONENTS Wt WtHTTP)

add_library(
  TemplateWt4WidgetsObj OBJECT
  WidgetsFactory.cpp
)

target_include_directories(
  TemplateWt4WidgetsObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${Wt_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4WidgetsObj
  wt wthttp
)

add_subdirectory(guest)
