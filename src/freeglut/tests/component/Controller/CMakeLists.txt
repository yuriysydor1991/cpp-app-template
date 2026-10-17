cmake_minimum_required(VERSION 3.13)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(
  CTEST_controller
  CTEST_controller.cpp
  ${CMAKE_SOURCE_DIR}/src/freeglut/FreeGlutController.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_controller
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${GLUT_INCLUDE_DIRS}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_controller
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
