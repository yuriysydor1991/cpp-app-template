cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBOAI
  "Set to ON to enable the liboai OpenAI API library (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_LIBOAI)
  return()
endif()

# The liboai CMake project requests both of it's dependencies through the
# find_package call, so a fetched (rather than an installed) copy of any of
# them stays invisible to it. Both are probed here in order to fail with a
# clear message instead of failing inside the fetched liboai project.
find_package(CURL QUIET)
find_package(nlohmann_json QUIET CONFIG)

if (NOT CURL_FOUND OR NOT nlohmann_json_FOUND)
  message(
    FATAL_ERROR
    "The liboai library requires the system wide installed libcurl and the "
    "nlohmann JSON development packages (the libcurl4-openssl-dev and the "
    "nlohmann-json3-dev ones for the Debian based distributions). Install "
    "them or set the ENABLE_LIBOAI option to OFF."
  )
endif()

set(TEMPLATE_APP_LIBOAI_GIT "https://github.com/d7ead/liboai.git" CACHE STRING "The liboai library git source repository")
set(TEMPLATE_APP_LIBOAI_GIT_TAG "main" CACHE STRING "The liboai project git repository tag of interest")

# The nlohmann JSON sources are described even with the ENABLE_NLOHMANN_JSON
# option left OFF, because the flatpak manifest builds the liboai dependency
# from them inside the sandbox where no system wide package is available.
set(TEMPLATE_APP_NLOHMANN_GIT "https://github.com/nlohmann/json.git" CACHE STRING "The Nlohmann JSON library git source repository")
set(TEMPLATE_APP_NLOHMANN_GIT_TAG "master" CACHE STRING "The Nlohmann JSON project git repository tag of interest")

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
