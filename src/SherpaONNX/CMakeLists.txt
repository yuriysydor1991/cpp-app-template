cmake_minimum_required(VERSION 3.13)

# The sherpa-onnx is a hard requirement of this branch rather than an optional
# integration, since the whole src/SherpaONNX example is built around it.
if (NOT ENABLE_SHERPA_ONNX)
  message(
    FATAL_ERROR
    "The src/SherpaONNX sources require the sherpa-onnx library which is turned off by "
    "the ENABLE_SHERPA_ONNX=OFF parameter. Drop the add_subdirectory(SherpaONNX) call from the "
    "src/CMakeLists.txt file together with the whole src/SherpaONNX subdirectory and "
    "provide another tts::ISpeechSynthesizer::create implementation to build the project without it."
  )
endif()

add_library(
  TemplateProjectSherpaONNXObj OBJECT
  KokoroModel.cpp
  SherpaONNXController.cpp
  SherpaONNXModel.cpp
  VitsModel.cpp
)

target_include_directories(
  TemplateProjectSherpaONNXObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The sherpa-onnx itself is made available by it's enabler. The PUBLIC keyword
# hands it's headers over to the sources above and it's libraries over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectSherpaONNXObj
  PUBLIC SherpaONNX::cxx-api
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectSherpaONNXObj
)

# The shared sherpa-onnx libraries, and the onnxruntime one it downloads where
# the distribution packages none, go into the private library directory of the
# project, which the installed executable finds them in by it's RPATH.
set(sherpaOnnxLibDir "${CMAKE_INSTALL_LIBDIR}/${PROJECT_BINARY_NAME}")

install(
  TARGETS sherpa-onnx-c-api sherpa-onnx-cxx-api
  LIBRARY DESTINATION ${sherpaOnnxLibDir}
  RUNTIME DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

FetchContent_GetProperties(onnxruntime)

if (onnxruntime_POPULATED)
  file(GLOB onnxruntimeLibs "${onnxruntime_SOURCE_DIR}/lib/*onnxruntime*${CMAKE_SHARED_LIBRARY_SUFFIX}*")
  install(FILES ${onnxruntimeLibs} DESTINATION ${sherpaOnnxLibDir})
endif()

get_filename_component(binDir "${PROJECT_BINARY_INSTALLATION_DIR}" ABSOLUTE BASE_DIR "${CMAKE_INSTALL_PREFIX}")
get_filename_component(libDir "${sherpaOnnxLibDir}" ABSOLUTE BASE_DIR "${CMAKE_INSTALL_PREFIX}")
file(RELATIVE_PATH binToLibDir "${binDir}" "${libDir}")

set_target_properties(
  ${PROJECT_BINARY_NAME}
  PROPERTIES INSTALL_RPATH "$ORIGIN/${binToLibDir}"
)

add_subdirectory(tests)
