cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_PLOTGENCPP
    "Enables the PlotGenCpp library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_PLOTGENCPP)
    return()
endif()

set(TEMPLATE_APP_PLOTGENCPP_GIT "https://github.com/skhelladi/PlotGenCpp.git")
set(TEMPLATE_APP_PLOTGENCPP_GIT_TAG "main")

find_package(PlotGenCpp QUIET)

if (PlotGenCpp_FOUND)
  message(STATUS "System already contains the PlotGenCpp library")
else()
  message(STATUS "The PlotGenCpp library is not available in the system")

  message(STATUS "PlotGenCpp was not found in the system (or probing is OFF)")
  message(STATUS "Trying to make PlotGenCpp library available through the Internet")

  message(STATUS "PlotGenCpp URL: ${TEMPLATE_APP_PLOTGENCPP_GIT}")
  message(STATUS "PlotGenCpp Tag: ${TEMPLATE_APP_PLOTGENCPP_GIT_TAG}")

  include(FetchContent)

  FetchContent_Declare(
    PlotGenCpp
    GIT_REPOSITORY ${TEMPLATE_APP_PLOTGENCPP_GIT}
    GIT_TAG        ${TEMPLATE_APP_PLOTGENCPP_GIT_TAG}
  )

  FetchContent_MakeAvailable(PlotGenCpp)

  install(TARGETS PlotGenCpp
    EXPORT PlotGenCpp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif()

target_link_libraries(
  TemplateProjectPlotGenCppControllerObj
  PlotGenCpp
)
