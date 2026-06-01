cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(
  PROJECT_BINARY_NAME ${PROJECT_NAME}
  CACHE STRING "Project main binary name and target"
)

string(TOLOWER ${PROJECT_BINARY_NAME} PROJECT_BINARY_NAME_lower)

set(
  QT6_OBJECT_NAME "${PROJECT_NAME}QT6Obj"
  CACHE STRING "Project Qt6 object library name and target"
)

set(
  PROJECT_URI "ua.org.kytok.template.Qt6.${PROJECT_BINARY_NAME}"
  CACHE STRING "Project reverse URL identifier"
)

set(
  PROJECT_MAINTAINER "Your Name"
  CACHE STRING "Project maintainer name (used for the DEB package)"
)

set(
  PROJECT_MAINTAINER_EMAIL "yourname@your.email.org"
  CACHE STRING "Project maintainer email (used for the DEB package)"
)

set(
  MAX_LOG_LEVEL "3"
  CACHE STRING 
  "Sets the maximum severity of the compiled log messages. Error=0. Trace=5. By default Info=3"
)

set(
  PROJECT_BINARY_INSTALLATION_DIR "bin"
  CACHE STRING 
  "Sets the project main binary installation directory"
)

set(
  DEFAULT_LOG_FILE_PATH ""
  CACHE STRING 
  "Sets the default log file path"
)

option(
  ENABLE_LOGS_MICROSECONDS_TIME
  "Set to OFF to disable the microseconds fields included into the log messages"
  ON
)

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S")

message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "PROJECT_BINARY_NAME: ${PROJECT_BINARY_NAME}")
message(STATUS "PROJECT_CONFIGURE_DATE: ${PROJECT_CONFIGURE_DATE}")
