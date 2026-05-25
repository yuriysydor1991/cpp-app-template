cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_PLOTGENCPP
    "Enables the PlotGenCpp library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_PLOTGENCPP)
    return()
endif()

set(TEMPLATE_APP_PLOTGENCPP_GIT "https://github.com/skhelladi/PlotGenCpp.git" CACHE STRING "The PlotGenCpp library git source repository")
set(TEMPLATE_APP_PLOTGENCPP_GIT_TAG "main" CACHE STRING "The PlotGenCpp library git source repository tag")

template_project_default_3rdparty_enabler(
  NAME PlotGenCpp 
  GIT_REPOSITORY ${TEMPLATE_APP_PLOTGENCPP_GIT}
  GIT_TAG        ${TEMPLATE_APP_PLOTGENCPP_GIT_TAG}
)

# install(TARGETS PlotGenCpp
#     EXPORT PlotGenCpp
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib
#     RUNTIME DESTINATION bin
#   )

target_link_libraries(
  TemplateProjectPlotGenCppControllerObj
  PlotGenCpp
)
