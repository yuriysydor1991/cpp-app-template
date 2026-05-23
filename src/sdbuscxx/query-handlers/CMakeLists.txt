cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectDBusQueryHandlersObj OBJECT
  Hostname1QueryHandler.cpp
  DBusQueryHandlerFactory.cpp
)

target_include_directories(
  TemplateProjectDBusQueryHandlersObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)


target_link_libraries(
  TemplateProjectDBusQueryHandlersObj
  ${SDBUSCPP_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectDBusQueryHandlersObj
)

add_subdirectory(tests)
