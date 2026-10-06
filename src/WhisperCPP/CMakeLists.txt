cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectWhisperControllerObj OBJECT
  Microphone.cpp
  UtteranceDetector.cpp
  WhisperController.cpp
)

target_include_directories(
  TemplateProjectWhisperControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The whisper.cpp and the SDL2 themselves are made available by their
# enablers. The PUBLIC keyword hands their headers over to the sources above
# and their libraries over to the executable which links this object library.
target_link_libraries(
  TemplateProjectWhisperControllerObj
  PUBLIC whisper ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectWhisperControllerObj
)

add_subdirectory(tests)
