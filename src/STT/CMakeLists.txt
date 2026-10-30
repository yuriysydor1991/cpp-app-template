cmake_minimum_required(VERSION 3.13)

# The engine neutral speech recognition sources: the microphone, the utterance
# detector, the recognizer interface and the listener of the three. The engine
# sources of the flavor implement the recognizer on top.
if (NOT ENABLE_SDL2_AUDIO)
  message(
    FATAL_ERROR
    "The src/STT sources capture the microphone through the SDL2 audio subsystem which is turned off by "
    "the ENABLE_SDL2_AUDIO=OFF parameter. Drop the Microphone class from the src/STT sources "
    "and its usage of the src/STT/SpeechListener.cpp file to build the project without it."
  )
endif()

add_library(
  TemplateProjectSTTObj OBJECT
  Microphone.cpp
  SpeechListener.cpp
  UtteranceDetector.cpp
)

target_include_directories(
  TemplateProjectSTTObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The SDL2 itself is made available by it's enabler. The PUBLIC keyword hands
# it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectSTTObj
  PUBLIC ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectSTTObj
)

add_subdirectory(tests)
