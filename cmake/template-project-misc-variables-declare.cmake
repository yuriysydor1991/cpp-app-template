cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# defines the CMAKE_INSTALL_* dirs and consumes the ones the flatpak-builder passes
include(GNUInstallDirs)

set(
  PROJECT_BINARY_NAME ${CMAKE_PROJECT_NAME}
  CACHE STRING "Project main binary name and target"
)

string(TOLOWER ${PROJECT_BINARY_NAME} PROJECT_BINARY_NAME_lower)

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

option(
  ENABLE_DESKTOP_APPLICATION
  "Set to ON when the project binary is a windowed application: the packages then install its desktop entry and mark it as a desktop application"
  OFF
)

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S")

set(PROJECT_CURL_MAX_RESPONSE_BYTES "8388608" CACHE STRING "The maximum accepted response size of a single libcurl request in bytes (8 MiB by default)")
set(PROJECT_CURL_CONNECT_TIMEOUT_SECONDS "10" CACHE STRING "The seconds a libcurl request may take to establish the connection")
set(PROJECT_CURL_TRANSFER_TIMEOUT_SECONDS "30" CACHE STRING "The seconds a whole libcurl download or reachability check may take")
set(PROJECT_CURL_POST_TIMEOUT_SECONDS "300" CACHE STRING "The seconds a whole libcurl POST request may take, the answer composing of the server included")
set(PROJECT_CURL_ALLOWED_PROTOCOLS "http,https,file" CACHE STRING "The comma separated protocols a libcurl request is allowed to use")

message(STATUS "CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message(STATUS "PROJECT_BINARY_NAME: ${PROJECT_BINARY_NAME}")
message(STATUS "PROJECT_CONFIGURE_DATE: ${PROJECT_CONFIGURE_DATE}")
