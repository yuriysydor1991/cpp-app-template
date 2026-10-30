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
  ${QT6_OBJECT_NAME}components
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Qt6Controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

# The QtWebEngine (Chromium) of the map view trips the new-delete check of the
# AddressSanitizer and leaves its allocations behind at exit, none of which is
# the project's code.
set_tests_properties(
  ${noArgsTests}
  PROPERTIES
    TIMEOUT 120
    ENVIRONMENT
      "QT_QPA_PLATFORM=offscreen;ASAN_OPTIONS=new_delete_type_mismatch=0:detect_leaks=0"
)
