cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SFMLContext
  UTEST_SFMLContext.cpp
  ${CMAKE_SOURCE_DIR}/src/SFML/SFMLContext.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SFMLContext
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_SFMLContext
  sfml-graphics
  sfml-window
  sfml-system
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SFMLContext
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
