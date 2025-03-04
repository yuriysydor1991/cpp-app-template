cmake_minimum_required(VERSION 3.22.1)

# Change the PROJECT_NAME var value to change executable name
set(
  PROJECT_NAME "CppAppTemplate"
  CACHE STRING "Project general name with an executable name"
)

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S %Z")

message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

project(
  ${PROJECT_NAME}
  VERSION 0.2.0
  DESCRIPTION "A C++ Template project for you!"
  HOMEPAGE_URL "http://www.kytok.org.ua/"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(Git REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(src)
