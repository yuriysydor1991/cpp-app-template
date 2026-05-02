cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBCURL
  "Set to ON to enable the libcurl (by using system wide available or through the Internet)"
  OFF
)

if (NOT ENABLE_LIBCURL)
  return()
endif()

set(TEMPLATE_APP_CURL_GIT "https://github.com/curl/curl.git")
set(TEMPLATE_APP_CURL_GIT_TAG "master")

find_package(CURL QUIET)

if (CURL_FOUND)
  message(STATUS "System already contains the CURL library")
  return()
else()
  message(STATUS "The CURL library is no available in the system")
endif()

message(STATUS "CURL was not found in the system (or probing is OFF)")
message(STATUS "Trying to make CURL library available through the Internet")

message(STATUS "CURL URL: ${TEMPLATE_APP_CURL_GIT}")
message(STATUS "CURL Tag: ${TEMPLATE_APP_CURL_GIT_TAG}")

include(FetchContent)

FetchContent_Declare(
  libcurl
  GIT_REPOSITORY ${TEMPLATE_APP_CURL_GIT}
  GIT_TAG        ${TEMPLATE_APP_CURL_GIT_TAG}
)

FetchContent_MakeAvailable(libcurl)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  CURL::libcurl
)
