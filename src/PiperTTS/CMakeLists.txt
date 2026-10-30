cmake_minimum_required(VERSION 3.13)

# The Piper is a hard requirement of this branch rather than an optional
# integration, since the whole src/PiperTTS example is built around it.
if (NOT ENABLE_PIPER)
  message(
    FATAL_ERROR
    "The src/PiperTTS sources require the Piper library which is turned off by "
    "the ENABLE_PIPER=OFF parameter. Drop the add_subdirectory(PiperTTS) call from the "
    "src/CMakeLists.txt file together with the whole src/PiperTTS subdirectory and "
    "provide another tts::ISpeechSynthesizer::create implementation to build the project without it."
  )
endif()

add_library(
  TemplateProjectPiperTTSObj OBJECT
  PiperController.cpp
)

target_include_directories(
  TemplateProjectPiperTTSObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The Piper itself is made available by it's enabler. The PUBLIC keyword hands
# it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectPiperTTSObj
  PUBLIC Piper::piper
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectPiperTTSObj
)

# The installed executable loads the libpiper the enabler installs into the
# library directory of the project.
set_target_properties(
  ${PROJECT_BINARY_NAME} PROPERTIES
  INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}/${PROJECT_BINARY_NAME}"
)

add_subdirectory(tests)
