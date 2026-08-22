cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(
  LIB_INCLUDE_MINOR_IN_NAME
  "Append .<minor> to the installable library name (binary, headers subdir, CMake package dir)"
  OFF
)

option(
  LIB_INCLUDE_MICRO_IN_NAME
  "Append .<micro> after the minor segment to the installable library name. Implies LIB_INCLUDE_MINOR_IN_NAME."
  OFF
)

set(
  LIB_NAME_SUFFIX ""
  CACHE STRING
  "Optional trailing suffix appended to the installable library name (e.g. '-dev')."
)

# The development files are everything an installation needs in order to build
# *against* the library rather than to *run* something linked with it: the
# public headers, the CMake package integration files, the unversioned .so
# namelink and any debug symbols the project decides to install. Turning this
# off produces a runtime only installation - the kind a distribution ships in
# its non -dev package.
option(
  LIB_INSTALL_DEV_FILES
  "Set to OFF to install the runtime library only, without the development files (public headers, CMake package files, the .so namelink and the debug symbols, if any)"
  ON
)

set(_lib_name "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION_MAJOR}")

if(LIB_INCLUDE_MICRO_IN_NAME AND NOT LIB_INCLUDE_MINOR_IN_NAME)
  message(WARNING
    "LIB_INCLUDE_MICRO_IN_NAME=ON requires LIB_INCLUDE_MINOR_IN_NAME=ON - "
    "enabling LIB_INCLUDE_MINOR_IN_NAME implicitly."
  )
  set(LIB_INCLUDE_MINOR_IN_NAME ON CACHE BOOL "" FORCE)
endif()

if(LIB_INCLUDE_MINOR_IN_NAME)
  set(_lib_name "${_lib_name}.${CMAKE_PROJECT_VERSION_MINOR}")
endif()

if(LIB_INCLUDE_MICRO_IN_NAME)
  set(_lib_name "${_lib_name}.${CMAKE_PROJECT_VERSION_PATCH}")
endif()

if(LIB_NAME_SUFFIX)
  set(_lib_name "${_lib_name}${LIB_NAME_SUFFIX}")
endif()

set(
  PROJECT_LIBRARY_NAME "${_lib_name}"
  CACHE STRING "Project main library name and target"
  FORCE
)

unset(_lib_name)

message(STATUS "PROJECT_LIBRARY_NAME: ${PROJECT_LIBRARY_NAME}")

# The library public C++ namespace. It is derived from the top level project
# name, so every project derived from this template owns a unique one and an
# application may depend on many derived libraries at once. Two libraries
# sharing a namespace share their symbols too, and the loader then silently
# binds every call of both of them into whichever library it resolved first.
string(MAKE_C_IDENTIFIER "${CMAKE_PROJECT_NAME}" _lib_namespace)

set(
  PROJECT_LIB_NAMESPACE "${_lib_namespace}_${CMAKE_PROJECT_VERSION_MAJOR}"
  CACHE STRING "The library public C++ namespace, unique per derived project"
  FORCE
)

unset(_lib_namespace)

message(STATUS "PROJECT_LIB_NAMESPACE: ${PROJECT_LIB_NAMESPACE}")

# The default logger implementation C++ namespace. Every derived library
# carries an own copy of the logging subsystem, so the copies must not share
# their symbols either: two libraries with a single logger namespace share the
# real logger instance holder too, and the loader then binds the logging calls
# of both of them into whichever library it resolved first. The logger::ILogger
# interface stays out of it on purpose - see its own documentation.
set(
  PROJECT_DEFAULT_LOG_NAMESPACE "${PROJECT_LIB_NAMESPACE}_default_logger"
  CACHE STRING
  "The default logger implementation C++ namespace, unique per derived project"
  FORCE
)

message(STATUS "PROJECT_DEFAULT_LOG_NAMESPACE: ${PROJECT_DEFAULT_LOG_NAMESPACE}")

# The directory the public headers are generated into. It is declared here and
# not in the src/lib subdirectory, because the analyzer targets are created
# before that subdirectory is added and have to reach those headers too.
set(
  PROJECT_LIB_PUBLIC_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include"
  CACHE PATH "The generated library public headers include directory"
  FORCE
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
