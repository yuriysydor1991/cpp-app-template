cmake_minimum_required(VERSION 3.13)

find_package(Boost REQUIRED COMPONENTS system thread)

add_library(
  TemplateBoostBeastObj OBJECT
  HttpController.cpp
  HttpContext.cpp
)

target_include_directories(
  TemplateBoostBeastObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${Wt_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateBoostBeastObj
  Boost::system
  Boost::thread
)
