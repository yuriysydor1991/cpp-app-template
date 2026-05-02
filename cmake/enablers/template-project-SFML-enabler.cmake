cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SFML
    "Enables the SFML library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_SFML)
    return()
endif()

set(TEMPLATE_APP_SFML_GIT "https://github.com/skhelladi/SFML.git")
set(TEMPLATE_APP_SFML_GIT_TAG "main")

find_package(SFML COMPONENTS graphics window system QUIET)

if (SFML_FOUND)
  message(STATUS "System already contains the SFML library")
else()
  message(STATUS "The SFML library is not available in the system")

  message(STATUS "SFML was not found in the system (or probing is OFF)")
  message(STATUS "Trying to make SFML library available through the Internet")

  message(STATUS "SFML URL: ${TEMPLATE_APP_SFML_GIT}")
  message(STATUS "SFML Tag: ${TEMPLATE_APP_SFML_GIT_TAG}")

  include(FetchContent)

  FetchContent_Declare(
    SFML
    GIT_REPOSITORY ${TEMPLATE_APP_SFML_GIT}
    GIT_TAG        ${TEMPLATE_APP_SFML_GIT_TAG}
  )

  FetchContent_MakeAvailable(SFML)
endif()

target_link_libraries(
  TemplateProjectPlotGenCppControllerObj
  sfml-graphics
  sfml-window
  sfml-system
)
