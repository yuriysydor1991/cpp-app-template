cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBCURL
  "Set to ON to enable the libcurl (by using system wide available or through the Internet)"
  OFF
)

if (NOT ENABLE_LIBCURL)
  return()
endif()

set(TEMPLATE_APP_CURL_GIT "https://github.com/curl/curl.git" CACHE STRING "The CURL library git source repository")
set(TEMPLATE_APP_CURL_GIT_TAG "master" CACHE STRING "The CURL project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME CURL 
  GIT_REPOSITORY ${TEMPLATE_APP_CURL_GIT}
  GIT_TAG ${TEMPLATE_APP_CURL_GIT_TAG}
)

target_link_libraries(
  ${PROJECT_LIBRARY_NAME}
  CURL::libcurl
)
