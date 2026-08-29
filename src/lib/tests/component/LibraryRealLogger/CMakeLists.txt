cmake_minimum_required(VERSION 3.13)

# disabling the asserts to let the library error paths be reachable
add_compile_options(-DNDEBUG=1)

# The library is expected to log into the real logger instance handed over by
# its user, so the whole library implementation is linked together with the
# real log.h facilities instead of the log mock and is driven through the
# public LibraryFacade only.
add_executable(
  CTEST_LibraryRealLogger
  CTEST_LibraryRealLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/facade/LibraryFacade.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/libmain/LibFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/libmain/LibMain.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_LibraryRealLogger
  PRIVATE CTEST_LibraryRealLogger_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_LibraryRealLogger
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/lib/facade/public
)

target_link_libraries(
  CTEST_LibraryRealLogger
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_LibraryRealLogger
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
