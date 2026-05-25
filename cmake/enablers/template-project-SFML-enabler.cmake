cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SFML
    "Enables the SFML library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_SFML)
    return()
endif()

set(TEMPLATE_APP_SFML_GIT "https://github.com/skhelladi/SFML.git" CACHE STRING "The SFML library git source repository")
set(TEMPLATE_APP_SFML_GIT_TAG "main" CACHE STRING "The SFML library git source repository tag")

# COMPONENTS graphics window system
template_project_default_3rdparty_enabler(
  NAME SFML 
  GIT_REPOSITORY ${TEMPLATE_APP_SFML_GIT}
  GIT_TAG        ${TEMPLATE_APP_SFML_GIT_TAG}
)

target_link_libraries(
  TemplateProjectPlotGenCppControllerObj
  sfml-graphics
  sfml-window
  sfml-system
)
