cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_PLPLOT
  "Set to ON to enable the PLplot integration (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_PLPLOT)
  return()
endif()

set(TEMPLATE_APP_PLPLOT_GIT "https://git.code.sf.net/p/plplot/plplot" CACHE STRING "The PLplot library git source repository")
set(TEMPLATE_APP_PLPLOT_GIT_TAG "master" CACHE STRING "The PLplot project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME plplot
  GIT_REPOSITORY ${TEMPLATE_APP_PLPLOT_GIT}
  GIT_TAG ${TEMPLATE_APP_PLPLOT_GIT_TAG}
  COMPONENTS CXX
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PLPLOT::plplot
  PLPLOT::plplotcxx
)
