cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateHTTPSessionHandlersObj OBJECT
  DefaultHandler.cpp
  HandlersFactory.cpp
  HTTPSessionContext.cpp
  RequestReader.cpp
)

target_include_directories(
  TemplateHTTPSessionHandlersObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateHTTPSessionHandlersObj
)
