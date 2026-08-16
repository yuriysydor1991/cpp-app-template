cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_CURLController
  CTEST_CURLController.cpp
  ${CMAKE_SOURCE_DIR}/src/CURL/CURLController.cpp
)

target_compile_definitions(
  CTEST_CURLController
  PRIVATE CTEST_CURLController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_CURLController
  PRIVATE ${CURL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CURL_INCLUDE_DIRS}
)

target_link_libraries(
  CTEST_CURLController
  GTest::gtest_main GTest::gmock
  CURL::libcurl
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_CURLController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
