cmake_minimum_required(VERSION 3.13)

# The whisper.cpp is a hard requirement of this branch rather than an optional
# integration, since the whole src/WhisperCPP example is built around it.
if (NOT ENABLE_WHISPERCPP)
  message(
    FATAL_ERROR
    "The src/WhisperCPP sources require the whisper.cpp library which is turned off by "
    "the ENABLE_WHISPERCPP=OFF parameter. Drop the add_subdirectory(WhisperCPP) call from the "
    "src/CMakeLists.txt file together with the whole src/WhisperCPP subdirectory "
    "and its usage of the src/app/applications/Application.cpp file to build "
    "the project without it."
  )
endif()

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
  PRIVATE TemplateProjectWhisperControllerObj
)

add_subdirectory(tests)
