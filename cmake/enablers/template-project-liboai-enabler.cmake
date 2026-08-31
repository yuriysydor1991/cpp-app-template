cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBOAI
  "Set to ON to enable the liboai OpenAI API library (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_LIBOAI)
  return()
endif()

set(TEMPLATE_APP_CURL_GIT "https://github.com/curl/curl.git" CACHE STRING "The CURL library git source repository")
set(TEMPLATE_APP_CURL_GIT_TAG "master" CACHE STRING "The CURL project git repository tag of interest")

set(TEMPLATE_APP_LIBOAI_GIT "https://github.com/d7ead/liboai.git" CACHE STRING "The liboai library git source repository")
set(TEMPLATE_APP_LIBOAI_GIT_TAG "main" CACHE STRING "The liboai project git repository tag of interest")

# The nlohmann JSON sources are described even with the ENABLE_NLOHMANN_JSON
# option left OFF, because the flatpak manifest builds the liboai dependency
# from them inside the sandbox where no system wide package is available.
set(TEMPLATE_APP_NLOHMANN_GIT "https://github.com/nlohmann/json.git" CACHE STRING "The Nlohmann JSON library git source repository")
set(TEMPLATE_APP_NLOHMANN_GIT_TAG "master" CACHE STRING "The Nlohmann JSON project git repository tag of interest")

# The liboai CMake project requests both of it's dependencies through the
# find_package call, so they are made available before it. A fetched copy
# answers such a call too, because the CMake redirects the package config of
# every FetchContent populated dependency since it's 3.24 version.
# A fetched nlohmann JSON keeps it's install rules off by default, which makes
# the liboai own install(EXPORT) call fail on the target it links.
set(JSON_Install ON CACHE BOOL "Install the nlohmann JSON CMake targets")

template_project_default_3rdparty_enabler(
  NAME nlohmann_json
  GIT_REPOSITORY ${TEMPLATE_APP_NLOHMANN_GIT}
  GIT_TAG ${TEMPLATE_APP_NLOHMANN_GIT_TAG}
)

template_project_default_3rdparty_enabler(
  NAME CURL
  GIT_REPOSITORY ${TEMPLATE_APP_CURL_GIT}
  GIT_TAG ${TEMPLATE_APP_CURL_GIT_TAG}
)

template_project_default_3rdparty_enabler(
  NAME oai
  GIT_REPOSITORY ${TEMPLATE_APP_LIBOAI_GIT}
  GIT_TAG ${TEMPLATE_APP_LIBOAI_GIT_TAG}
)

# The installed liboai exports the oai::oai target while the fetched one
# declares the plain oai library only, so the alias gives both the same name.
if (NOT TARGET oai::oai)
  # An imported target carries it's headers as the system wide ones already,
  # while a fetched one does not, so it's third party warnings would reach the
  # project build (and break it with the COMPILE_WARNINGS_AS_ERRORS option on).
  get_target_property(TEMPLATE_APP_LIBOAI_INCLUDES oai INTERFACE_INCLUDE_DIRECTORIES)

  set_target_properties(
    oai PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${TEMPLATE_APP_LIBOAI_INCLUDES}"
  )

  add_library(oai::oai ALIAS oai)
endif()
