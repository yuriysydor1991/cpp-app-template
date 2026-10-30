cmake_minimum_required(VERSION 3.16)

# Component test: the real Qt6Controller loads the real QML modules of the
# project on the offscreen platform and leaves its event loop on the raised
# stop flag of a real application context.
add_executable(
  CTEST_Qt6Controller
  CTEST_Qt6Controller.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_Qt6Controller
  PRIVATE CTEST_Qt6Controller_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_Qt6Controller
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_Qt6Controller
  GTest::gtest_main GTest::gmock
  ${QT6_OBJECT_NAME} ${QT6_OBJECT_NAME}log ${QT6_OBJECT_NAME}main
  ${QT6_OBJECT_NAME}components ${QT6_OBJECT_NAME}constants
  ${QT6_OBJECT_NAME}resources
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Qt6Controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(
  ${noArgsTests} PROPERTIES TIMEOUT 120 ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
)
