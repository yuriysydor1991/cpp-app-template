cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSFMLEventsHandlersObj OBJECT
  EventClosedHandler.cpp
  EventsHandlersFactory.cpp
)

target_include_directories(
  TemplateSFMLEventsHandlersObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSFMLEventsHandlersObj
  PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSFMLEventsHandlersObj
)
