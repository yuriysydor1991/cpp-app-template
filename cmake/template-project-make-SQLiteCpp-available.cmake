cmake_minimum_required(VERSION 3.13)

set(TEMPLATE_APP_SQLITECPP_GIT "https://github.com/SRombauts/SQLiteCpp.git")
set(TEMPLATE_APP_SQLITECPP_GIT_TAG "3.3.3")

message(STATUS "Trying to probe the system SQLite")

find_package(SQLiteCpp QUIET)
find_package(Threads QUIET)
    
if(SQLiteCpp_FOUND)
  return()
endif()

message(STATUS "SQLite was not found in the system (or probing is OFF)")
message(STATUS "Trying to make SQLite available through the Internet")

message(STATUS "SQLite URL: ${TEMPLATE_APP_SQLITECPP_GIT}")
message(STATUS "SQLite Tag: ${TEMPLATE_APP_SQLITECPP_GIT_TAG}")

include(FetchContent)

FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY ${TEMPLATE_APP_SQLITECPP_GIT}
  GIT_TAG        ${TEMPLATE_APP_SQLITECPP_GIT_TAG}
)

FetchContent_MakeAvailable(SQLiteCpp)
