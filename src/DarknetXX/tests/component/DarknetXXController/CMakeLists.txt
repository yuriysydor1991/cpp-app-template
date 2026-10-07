cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the darknetxx
# messages and the controller ones get into the project log.
add_executable(
  CTEST_DarknetXXController
  CTEST_DarknetXXController.cpp
)

target_compile_definitions(
  CTEST_DarknetXXController
  PRIVATE
    CTEST_DarknetXXController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
    CTEST_DarknetXXController_CFG=\"${PROJECT_DARKNETXX_CFG_PATH}\"
    CTEST_DarknetXXController_WEIGHTS=\"${PROJECT_DARKNETXX_WEIGHTS_PATH}\"
    CTEST_DarknetXXController_NAMES=\"${PROJECT_DARKNETXX_NAMES_PATH}\"
    CTEST_DarknetXXController_IMAGE=\"${PROJECT_DARKNETXX_IMAGE_PATH}\"
)

target_include_directories(
  CTEST_DarknetXXController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_DarknetXXController
  ${DARKNETXX_TESTS_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_DarknetXXController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
