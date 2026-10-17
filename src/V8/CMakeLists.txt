cmake_minimum_required(VERSION 3.13)

# The V8 is a hard requirement of this branch rather than an optional
# integration, since the whole src/V8 example is built around it.
if (NOT ENABLE_V8)
  message(
    FATAL_ERROR
    "The src/V8 sources require the V8 library which is turned off by "
    "the ENABLE_V8=OFF parameter. Drop the add_subdirectory(V8) call from the "
    "src/CMakeLists.txt file together with the whole src/V8 subdirectory "
    "and its usage of the src/app/applications/Application.cpp file to build "
    "the project without it."
  )
endif()

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
  PRIVATE TemplateProjectV8ControllerObj
)

add_subdirectory(tests)
