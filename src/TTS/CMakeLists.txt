cmake_minimum_required(VERSION 3.13)

# The engine neutral text to speech sources: the speech, the synthesizer
# interface and the WAV file and the SDL2 playback outputs of the speech. The
# engine sources of the flavor implement the synthesizer on top.
if (NOT ENABLE_SDL2_AUDIO)
  message(
    FATAL_ERROR
    "The src/TTS sources play the speech through the SDL2 audio subsystem which is turned off by "
    "the ENABLE_SDL2_AUDIO=OFF parameter. Drop the AudioPlayer class from the src/TTS sources "
    "and its usage of the src/app/applications/Application.cpp file to build the project without it."
  )
endif()

add_library(
  TemplateProjectTTSObj OBJECT
  AudioPlayer.cpp
  Speech.cpp
  WavWriter.cpp
)

target_include_directories(
  TemplateProjectTTSObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The SDL2 itself is made available by it's enabler. The PUBLIC keyword hands
# it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectTTSObj
  PUBLIC ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectTTSObj
)

add_subdirectory(tests)
