cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_EventsHandlersFactory
  UTEST_EventsHandlersFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventClosedHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/SFMLContext.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_EventsHandlersFactory
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_EventsHandlersFactory
  sfml-graphics
  sfml-window
  sfml-system
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_EventsHandlersFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
