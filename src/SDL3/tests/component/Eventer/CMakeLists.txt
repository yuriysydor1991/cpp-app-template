cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_eventer
  CTEST_eventer.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL3/Eventer/EventsController.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL3/Eventer/EventsHandlers/EventQuitHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/SDL3/SDL3Context.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_eventer
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_eventer
  SDL3::SDL3
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_eventer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
