cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_EventClosedHandler
  UTEST_EventClosedHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventClosedHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/SFMLContext.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_EventClosedHandler
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_EventClosedHandler
  sfml-graphics
  sfml-window
  sfml-system
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_EventClosedHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
