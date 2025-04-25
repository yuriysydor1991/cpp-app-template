cmake_minimum_required(VERSION 3.13)

find_package(Wt REQUIRED COMPONENTS Wt WtHTTP)

add_library(
  TemplateWt4Obj OBJECT
  Wt4Server.cpp
)

target_include_directories(
  TemplateWt4Obj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${Wt_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4Obj
  wt wthttp
)
