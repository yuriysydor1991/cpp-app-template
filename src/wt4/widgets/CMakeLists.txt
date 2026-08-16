cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateWt4WidgetsObj OBJECT
  WidgetsFactory.cpp
)

target_include_directories(
  TemplateWt4WidgetsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateWt4WidgetsObj
  PUBLIC Wt::Wt Wt::HTTP
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4WidgetsObj
)

add_subdirectory(guest)
