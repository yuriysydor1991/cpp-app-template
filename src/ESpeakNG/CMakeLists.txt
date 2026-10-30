cmake_minimum_required(VERSION 3.13)

# The eSpeak NG is a hard requirement of this branch rather than an optional
# integration, since the whole src/ESpeakNG example is built around it.
if (NOT ENABLE_ESPEAK_NG)
  message(
    FATAL_ERROR
    "The src/ESpeakNG sources require the eSpeak NG library which is turned off by "
    "the ENABLE_ESPEAK_NG=OFF parameter. Drop the add_subdirectory(ESpeakNG) call from the "
    "src/CMakeLists.txt file together with the whole src/ESpeakNG subdirectory and "
    "provide another tts::ISpeechSynthesizer::create implementation to build the project without it."
  )
endif()

add_library(
  TemplateProjectESpeakNGObj OBJECT
  ESpeakNGController.cpp
)

target_include_directories(
  TemplateProjectESpeakNGObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The eSpeak NG itself is made available by it's enabler. The PUBLIC keyword
# hands it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectESpeakNGObj
  PUBLIC ESpeakNG::espeak-ng
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectESpeakNGObj
)

add_subdirectory(tests)
