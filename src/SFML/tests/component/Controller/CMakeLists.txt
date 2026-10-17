cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_controller
  CTEST_controller.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/SFMLController.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/SFMLContext.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/SFMLContextBuilder.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/Painter/Painter.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/Eventer/EventsController.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventClosedHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_controller
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_controller
  sfml-graphics
  sfml-window
  sfml-system
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
