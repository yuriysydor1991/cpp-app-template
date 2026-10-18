cmake_minimum_required(VERSION 3.13)

# The sherpa-onnx configuration structures alone are used, so the headers of
# the library are enough.
add_executable(
  UTEST_SherpaONNXModel
  UTEST_SherpaONNXModel.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/KokoroModel.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/SherpaONNXModel.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/VitsModel.cpp
)

target_compile_definitions(
  UTEST_SherpaONNXModel
  PRIVATE UTEST_SherpaONNXModel_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_SherpaONNXModel
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_include_directories(
  UTEST_SherpaONNXModel
  SYSTEM PRIVATE $<TARGET_PROPERTY:SherpaONNX::cxx-api,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(
  UTEST_SherpaONNXModel
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SherpaONNXModel
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
