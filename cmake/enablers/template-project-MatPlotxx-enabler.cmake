cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_MATPLOTCXX
  "Set to ON to enable the MatPlotC++ (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_MATPLOTCXX)
  return()
endif()

set(TEMPLATE_APP_MATPLOTCXX_GIT "https://github.com/alandefreitas/matplotplusplus.git" CACHE STRING "The Matplot++ library git source repository")
set(TEMPLATE_APP_MATPLOTCXXL_GIT_TAG "master" CACHE STRING "The Matplot++ project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME Matplot++
  GIT_REPOSITORY ${TEMPLATE_APP_MATPLOTCXX_GIT}
  GIT_TAG        ${TEMPLATE_APP_MATPLOTCXXL_GIT_TAG}
)
