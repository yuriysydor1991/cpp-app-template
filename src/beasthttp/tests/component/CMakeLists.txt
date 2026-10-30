cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

# Boost.System is header only since the 1.69 release, so the modern Boost
# packages ship no CMake target of it's own for it, while the older ones
# still need it linked. Hence the optional request and the guarded link
# below.
find_package(Boost REQUIRED OPTIONAL_COMPONENTS system)
find_package(Threads REQUIRED)

add_executable(
  CTEST_beasthttp  
  CTEST_beasthttp.cpp
  HTTPHelper.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/HttpContext.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/HttpController.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/ResponseWriter.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/ResponseBuilder.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/RequestReader.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/HTTPSessionContext.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/HandlersFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/rhandlers/DefaultHandler.cpp
  ${PROJECT_SOURCE_DIR}/src/beasthttp/pages/PageBuilder.cpp
  ${APP_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

# TODO: introduce mocks for the external components
target_include_directories(
  CTEST_beasthttp
  PRIVATE
    ${APP_MOCKS_ROOT}/ApplicationContext
    ${APP_MOCKS_ROOT}/log
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_beasthttp
  GTest::gtest_main GTest::gmock
  Boost::boost Threads::Threads
)

if (TARGET Boost::system)
  target_link_libraries(CTEST_beasthttp Boost::system)
endif()

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_beasthttp
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
