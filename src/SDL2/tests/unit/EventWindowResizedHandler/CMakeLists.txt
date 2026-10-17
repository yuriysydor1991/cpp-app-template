cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_EventWindowResizedHandler
  UTEST_EventWindowResizedHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL2/Eventer/EventsHandlers/EventWindowResizedHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL2/SDL2Context.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_EventWindowResizedHandler
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_EventWindowResizedHandler
  SDL2::SDL2
  ${OPENGL_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_EventWindowResizedHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
