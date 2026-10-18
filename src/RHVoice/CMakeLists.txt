cmake_minimum_required(VERSION 3.13)

# The RHVoice is a hard requirement of this branch rather than an optional
# integration, since the whole src/RHVoice example is built around it.
if (NOT ENABLE_RHVOICE)
  message(
    FATAL_ERROR
    "The src/RHVoice sources require the RHVoice library which is turned off by "
    "the ENABLE_RHVOICE=OFF parameter. Drop the add_subdirectory(RHVoice) call from the "
    "src/CMakeLists.txt file together with the whole src/RHVoice subdirectory and "
    "provide another tts::ISpeechSynthesizer::create implementation to build the project without it."
  )
endif()

add_library(
  TemplateProjectRHVoiceObj OBJECT
  RHVoiceController.cpp
)

target_include_directories(
  TemplateProjectRHVoiceObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The RHVoice itself is made available by it's enabler. The PUBLIC keyword
# hands it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectRHVoiceObj
  PUBLIC RHVoice::RHVoice
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectRHVoiceObj
)

add_subdirectory(tests)
