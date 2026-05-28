cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSFMLObj OBJECT
  SFMLIniter.cpp
  SFMLContext.cpp
  SFMLContextBuilder.cpp
)

target_include_directories(
  TemplateSFMLObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSFMLObj
  PUBLIC
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSFMLObj
)

add_subdirectory(Painter)
add_subdirectory(Eventer)

if(ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS)
  add_subdirectory(tests)
endif()
