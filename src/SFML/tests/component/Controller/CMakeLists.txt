cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_controller
  CTEST_controller.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/SFMLController.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/SFMLContext.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/SFMLContextBuilder.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Painter/Painter.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Eventer/EventsController.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventClosedHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_controller
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
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
