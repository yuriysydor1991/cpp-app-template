cmake_minimum_required(VERSION 3.13)

# The llama.cpp is a hard requirement of this branch rather than an optional
# integration, since the whole src/LlamaCPP example is built around it.
if (NOT ENABLE_LLAMACPP)
  message(
    FATAL_ERROR
    "The src/LlamaCPP sources require the llama.cpp library which is turned off by "
    "the ENABLE_LLAMACPP=OFF parameter. Drop the add_subdirectory(LlamaCPP) call from the "
    "src/CMakeLists.txt file together with the whole src/LlamaCPP subdirectory "
    "and its usage of the src/app/applications/Application.cpp file to build "
    "the project without it."
  )
endif()

add_library(
  TemplateProjectLlamaCPPObj OBJECT
  BuiltinChatTemplate.cpp
  ChatTemplate.cpp
  Gemma4ChatTemplate.cpp
  LlamaCPPController.cpp
)

target_include_directories(
  TemplateProjectLlamaCPPObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The llama.cpp itself is made available by it's enabler. The PUBLIC keyword
# hands it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectLlamaCPPObj
  PUBLIC llama
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectLlamaCPPObj
)

add_subdirectory(tests)
