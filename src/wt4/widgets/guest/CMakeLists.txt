cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateWt4GuestWidgetsObj OBJECT
  Root.cpp
)

target_include_directories(
  TemplateWt4GuestWidgetsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateWt4GuestWidgetsObj
  PUBLIC Wt::Wt Wt::HTTP
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateWt4GuestWidgetsObj
)
