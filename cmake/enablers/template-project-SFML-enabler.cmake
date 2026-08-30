cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SFML
    "Enables the SFML library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_SFML)
    return()
endif()

set(TEMPLATE_APP_SFML_GIT "https://github.com/SFML/SFML.git" CACHE STRING "The SFML library git source repository")
# The PlotGenCpp library and the sfml-graphics, sfml-window and sfml-system
# target names below belong to the SFML 2 line, so the fallback clone points to
# its latest release and not to the SFML 3 default branch.
set(TEMPLATE_APP_SFML_GIT_TAG "2.6.2" CACHE STRING "The SFML library git source repository tag")

# Neither this project nor the PlotGenCpp library touches the audio and the
# network modules, so the fallback clone skips them and the OpenAL development
# package the audio one demands.
set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build the SFML audio module")
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build the SFML network module")

# COMPONENTS graphics window system
template_project_default_3rdparty_enabler(
  NAME SFML
  GIT_REPOSITORY ${TEMPLATE_APP_SFML_GIT}
  GIT_TAG        ${TEMPLATE_APP_SFML_GIT_TAG}
  COMPONENTS     graphics window system
)

target_link_libraries(
  TemplateProjectPlotGenCppControllerObj
  sfml-graphics
  sfml-window
  sfml-system
)
