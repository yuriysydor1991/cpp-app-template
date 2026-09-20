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

set(PROJECT_HTTP_LISTEN_ADDRESS "127.0.0.1" CACHE STRING "The default HTTP-server listen address")
set(PROJECT_HTTP_LISTEN_PORT "8080" CACHE STRING "The default HTTP-server listen port")

set(PROJECT_HTTP_MAX_REQUEST_BODY_BYTES "8388608" CACHE STRING "The maximum accepted HTTP request body size in bytes (8 MiB by default)")
set(PROJECT_HTTP_MAX_REQUEST_HEADER_BYTES "8192" CACHE STRING "The maximum accepted HTTP request header size in bytes (8 KiB by default)")
set(PROJECT_HTTP_REQUEST_TIMEOUT_SECONDS "30" CACHE STRING "The seconds a single HTTP request reading may take before the connection is dropped")
set(PROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS "30" CACHE STRING "The seconds a single HTTP response writing may take before the connection is dropped")
set(PROJECT_HTTP_MAX_CONNECTIONS "128" CACHE STRING "The maximum number of the simultaneously served HTTP connections")
set(PROJECT_HTTP_LISTEN_BACKLOG "128" CACHE STRING "The maximum number of the accepted connections waiting to be served")

message(STATUS "PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message(STATUS "PROJECT_BINARY_NAME: ${PROJECT_BINARY_NAME}")
message(STATUS "PROJECT_CONFIGURE_DATE: ${PROJECT_CONFIGURE_DATE}")
