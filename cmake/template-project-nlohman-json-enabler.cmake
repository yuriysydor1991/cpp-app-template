cmake_minimum_required(VERSION 3.13)

set(TEMPLATE_APP_NLOHMANN_GIT "https://github.com/nlohmann/json.git")
set(TEMPLATE_APP_NLOHMANN_GIT_TAG "master")

find_package(nlohmann_json QUIET)

if (NLOHMANN_JSON_FOUND)
  message(STATUS "System already contains the nlohmann json library")
  return()
else()
  message(STATUS "The nlohmann json library is no available in the library")
endif()

message(STATUS "NLOHMANN was not found in the system (or probing is OFF)")
message(STATUS "Trying to make nlohmann json library available through the Internet")

message(STATUS "NLOHMANN URL: ${TEMPLATE_APP_NLOHMANN_GIT}")
message(STATUS "NLOHMANN Tag: ${TEMPLATE_APP_NLOHMANN_GIT_TAG}")

include(FetchContent)

FetchContent_Declare(
  nlohmann-json
  GIT_REPOSITORY ${TEMPLATE_APP_NLOHMANN_GIT}
  GIT_TAG        ${TEMPLATE_APP_NLOHMANN_GIT_TAG}
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(NLOHMANN_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(nlohmann-json)
