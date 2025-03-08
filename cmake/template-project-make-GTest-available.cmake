cmake_minimum_required(VERSION 3.13)

set(TEMPLATE_APP_GTEST_GIT "https://github.com/google/googletest.git")
set(TEMPLATE_APP_GTEST_GIT_TAG "v1.16.0")

if (GTEST_TRY_SYSTEM_PROBE)
  message(STATUS "Trying to probe the system GTest")
  find_package(GTest QUIET)
else()
  message(STATUS "The system GTest available probing is OFF")
endif()
    
if(GTest_FOUND)
  return()
endif()

message(STATUS "GTest was not found in the system (or probing is OFF)")
message(STATUS "Trying to make GTest available through the Internet")

message(STATUS "GTest URL: ${TEMPLATE_APP_GTEST_GIT}")
message(STATUS "GTest Tag: ${TEMPLATE_APP_GTEST_GIT_TAG}")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY ${TEMPLATE_APP_GTEST_GIT}
  GIT_TAG        ${TEMPLATE_APP_GTEST_GIT_TAG}
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
