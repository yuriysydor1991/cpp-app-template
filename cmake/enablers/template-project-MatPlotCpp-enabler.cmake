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

# The library probes for a system installed SFML only, so the FetchContent
# provided one has to be handed over to it explicitly. Its CMakeLists pins the
# build type of its own directory to Release, so the SFML debug name postfix
# has to go, or the link asks for a library the Debug build never produces.
if (TARGET sfml-graphics)
  set_target_properties(
    sfml-graphics
    sfml-window
    sfml-system
    PROPERTIES DEBUG_POSTFIX ""
  )

  target_link_libraries(
    PlotGenCpp
    PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
  )
endif()

# The library sources reach for std::uint8_t without including <cstdint>, which
# the libstdc++ 15 headers no longer drag in on their own.
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(PlotGenCpp PRIVATE -include cstdint)
endif()

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
