cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_NLOHMANN_JSON
  "Set to ON to enable the nlohmann json library (by using system wide available or through Internet)"
  OFF
)

if (NOT ENABLE_NLOHMANN_JSON)
  return()
endif()

set(TEMPLATE_APP_NLOHMANN_GIT "https://github.com/nlohmann/json.git" CACHE STRING "The Nlohmann JSON library git source repository")
set(TEMPLATE_APP_NLOHMANN_GIT_TAG "master" CACHE STRING "The Nlohmann JSON project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME nlohmann_json 
  GIT_REPOSITORY ${TEMPLATE_APP_NLOHMANN_GIT}
  GIT_TAG ${TEMPLATE_APP_NLOHMANN_GIT_TAG}
)

target_link_libraries(
  ${PROJECT_LIBRARY_NAME}
  nlohmann_json::nlohmann_json
)
