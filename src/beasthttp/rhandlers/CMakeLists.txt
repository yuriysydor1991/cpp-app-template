cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateHTTPSessionHandlersObj OBJECT
  DefaultHandler.cpp
  HandlersFactory.cpp
  HTTPSessionContext.cpp
  RequestReader.cpp
  ResponseBuilder.cpp
  ResponseWriter.cpp
)

target_include_directories(
  TemplateHTTPSessionHandlersObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateHTTPSessionHandlersObj
  PUBLIC Boost::boost
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateHTTPSessionHandlersObj
)
