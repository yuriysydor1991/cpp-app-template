cmake_minimum_required(VERSION 3.13)

# Reusable enabler module for the Firebird client library (fbclient).
#
# Mirrors the libcurl/LibXml2/nlohmann-json enablers: it delegates to the
# shared template_project_default_3rdparty_enabler, which probes the system
# installation first and only falls back to fetching the upstream sources when
# nothing is found. The system probe is performed through the project
# cmake/FindFirebird.cmake module, which exposes the Firebird::fbclient imported
# target the Firebird driver links against.
#
# Building Firebird from source is heavy and seldom needed: the development
# package (for example 'sudo apt install -y firebird-dev') is the expected and
# supported path.

option(
  ENABLE_FIREBIRD
  "Set to ON to enable the Firebird client library (fbclient) integration"
  ON
)

if (NOT ENABLE_FIREBIRD)
  return()
endif()

set(TEMPLATE_APP_FIREBIRD_GIT "https://github.com/FirebirdSQL/firebird.git" CACHE STRING "The Firebird library git source repository")
set(TEMPLATE_APP_FIREBIRD_GIT_TAG "master" CACHE STRING "The Firebird project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME Firebird
  GIT_REPOSITORY ${TEMPLATE_APP_FIREBIRD_GIT}
  GIT_TAG ${TEMPLATE_APP_FIREBIRD_GIT_TAG}
)
