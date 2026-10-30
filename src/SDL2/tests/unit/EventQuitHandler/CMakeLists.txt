cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_EventQuitHandler
  UTEST_EventQuitHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL2/Eventer/EventsHandlers/EventQuitHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL2/SDL2Context.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_EventQuitHandler
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_EventQuitHandler
  SDL2::SDL2
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_EventQuitHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
