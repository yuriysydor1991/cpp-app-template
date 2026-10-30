cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_eventer
  CTEST_eventer.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/Eventer/EventsController.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/Eventer/EventsHandlers/EventQuitHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/Eventer/EventsHandlers/EventWindowResizedHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/SDL3Context.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/SDL3ContextBuilder.cpp
  ${PROJECT_SOURCE_DIR}/src/SDL3/OpenGLIniter.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_eventer
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_eventer
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_eventer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
