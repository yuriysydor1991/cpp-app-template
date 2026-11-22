cmake_minimum_required(VERSION 3.13)

# The ONNX Runtime adaptor the pose estimation engines run their models with.
if (NOT ENABLE_ONNXRUNTIME)
  message(
    FATAL_ERROR
    "The src/ONNX sources run the models with the ONNX Runtime library which is turned off by "
    "the ENABLE_ONNXRUNTIME=OFF parameter. Drop the add_subdirectory(ONNX) call from the "
    "src/CMakeLists.txt file together with the whole src/ONNX subdirectory and it's usage "
    "by the engine sources to build the project without it."
  )
endif()

find_package(OpenCV REQUIRED COMPONENTS core)

add_library(
  TemplateProjectONNXObj OBJECT
  ONNXModel.cpp
)

target_include_directories(
  TemplateProjectONNXObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The ONNX Runtime itself is made available by it's enabler. The PUBLIC
# keyword hands it's headers over to the sources above and it's library over
# to the executable which links this object library.
target_link_libraries(
  TemplateProjectONNXObj
  PUBLIC onnxruntime::onnxruntime ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectONNXObj
)

add_subdirectory(tests)
