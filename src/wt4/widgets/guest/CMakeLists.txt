cmake_minimum_required(VERSION 3.13)

find_package(Wt REQUIRED COMPONENTS Wt WtHTTP)

add_library(
  TemplateWt4GuestWidgetsObj OBJECT
  Root.cpp
)

target_include_directories(
  TemplateWt4GuestWidgetsObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${Wt_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4GuestWidgetsObj
  wt wthttp
)
