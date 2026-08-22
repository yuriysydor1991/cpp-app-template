cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectFontAwesomeStylesObj OBJECT
  FontAwesomeSolidStyle.cpp
  FontAwesomeRegularStyle.cpp
  FontAwesomeBrandsStyle.cpp
  FontAwesomeStyles.cpp
)

target_include_directories(
  TemplateProjectFontAwesomeStylesObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFontAwesomeStylesObj
)
