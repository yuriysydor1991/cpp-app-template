cmake_minimum_required(VERSION 3.13)

# The mocked sherpa-onnx library takes the place of the real one, whose headers
# alone are used.
add_executable(
  UTEST_SherpaONNXController
  UTEST_SherpaONNXController.cpp
  ${SHERPAONNX_MOCKS_ROOT}/SherpaONNXLibrary/SherpaONNXLibraryMock.cpp
  ${PROJECT_SOURCE_DIR}/src/SherpaONNX/SherpaONNXController.cpp
)

target_compile_definitions(
  UTEST_SherpaONNXController
  PRIVATE UTEST_SherpaONNXController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_SherpaONNXController
  PRIVATE ${SHERPAONNX_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
  UTEST_SherpaONNXController
  SYSTEM PRIVATE $<TARGET_PROPERTY:SherpaONNX::cxx-api,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(
  UTEST_SherpaONNXController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SherpaONNXController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
