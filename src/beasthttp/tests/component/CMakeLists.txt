cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

# Boost.System is header only since the 1.69 release, so the modern Boost
# packages ship no CMake target of it's own for it, while the older ones
# still need it linked. Hence the optional request and the guarded link
# below.
find_package(Boost REQUIRED COMPONENTS thread OPTIONAL_COMPONENTS system)

add_executable(
  CTEST_beasthttp  
  CTEST_beasthttp.cpp
  HTTPHelper.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/HttpContext.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/HttpController.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/ResponseWriter.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/ResponseBuilder.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/RequestReader.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/HTTPSessionContext.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/HandlersFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/rhandlers/DefaultHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/beasthttp/pages/PageBuilder.cpp
  ${GLOBAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

# TODO: introduce mocks for the external components
target_include_directories(
  CTEST_beasthttp
  PRIVATE
    ${GLOBAL_MOCKS_ROOT}/ApplicationContext
    ${GLOBAL_MOCKS_ROOT}/log
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_beasthttp
  GTest::gtest_main GTest::gmock
  Boost::thread
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
