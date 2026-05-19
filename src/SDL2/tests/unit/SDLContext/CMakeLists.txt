cmake_minimum_required(VERSION 3.13)

find_package(SDL2 REQUIRED)

add_executable(
  UTEST_SDLContext
  UTEST_SDLContext.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL2/SDL2Context.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SDLContext
  PRIVATE ${SDL2_INCLUDE_DIRS}
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_SDLContext
  ${SDL2_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SDLContext
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
