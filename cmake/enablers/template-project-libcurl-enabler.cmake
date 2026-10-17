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
set(TEMPLATE_APP_CURL_GIT_TAG "curl-8_23_0" CACHE STRING "The CURL project git repository release tag of interest")

template_project_default_3rdparty_enabler(
  NAME CURL 
  GIT_REPOSITORY ${TEMPLATE_APP_CURL_GIT}
  GIT_TAG ${TEMPLATE_APP_CURL_GIT_TAG}
)

# the library target holds the whole project code
target_link_libraries(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE
    CURL::libcurl
)
