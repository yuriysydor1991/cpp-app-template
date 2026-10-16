cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_Wt4Server
  CTEST_Wt4Server.cpp
  TestHttpClient.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/Wt4ArgsFilter.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/Wt4Context.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/Wt4Server.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/widgets/WidgetsFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/widgets/guest/Root.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_Wt4Server
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_Wt4Server
  GTest::gtest_main GTest::gmock Wt::Wt Wt::HTTP
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Wt4Server
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
