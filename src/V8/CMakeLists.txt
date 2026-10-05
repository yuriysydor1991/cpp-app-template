cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectV8ControllerObj OBJECT
  V8Console.cpp
  V8Controller.cpp
  V8Platform.cpp
)

target_include_directories(
  TemplateProjectV8ControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The V8 itself is made available by the V8 enabler. The PUBLIC keyword hands
# its headers over to the sources above and its library over to the executable
# which links this object library.
target_link_libraries(
  TemplateProjectV8ControllerObj
  PUBLIC V8::V8
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectV8ControllerObj
)

add_subdirectory(tests)
