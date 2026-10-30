cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Application  
  UTEST_Application.cpp
  ${PROJECT_SOURCE_DIR}/src/app/applications/Application.cpp
  ${PROJECT_SOURCE_DIR}/src/app/DataLocator.cpp
  ${APP_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
  ${PROJECT_SOURCE_DIR}/src/DarknetXX/Detection.cpp
  ${PROJECT_SOURCE_DIR}/src/DarknetXX/weights/Dxxwjz1Weights.cpp
  ${PROJECT_SOURCE_DIR}/src/DarknetXX/weights/Dxxwjz2Weights.cpp
  ${PROJECT_SOURCE_DIR}/src/DarknetXX/weights/NetworkWeights.cpp
  ${PROJECT_SOURCE_DIR}/src/DarknetXX/weights/OrigWeights.cpp
)

target_include_directories(
  UTEST_Application
  PRIVATE ${APP_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${APP_MOCKS_ROOT}/project-global-decls
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${APP_MOCKS_ROOT}/DarknetXXController
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Application
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Application
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
