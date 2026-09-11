cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectFreesoundCategoriesObj OBJECT
  FreesoundCategory.cpp
  FreesoundCategories.cpp
)

target_include_directories(
  TemplateProjectFreesoundCategoriesObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundCategoriesObj
)
