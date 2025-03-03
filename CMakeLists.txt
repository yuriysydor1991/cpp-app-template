cmake_minimum_required(VERSION 3.22.1)

# Change the PROJECT_NAME var value to change executable name
set(
  PROJECT_NAME "CppAppTemplate"
  CACHE STRING "Project general name with a executable name"
)

string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d %H:%M:%S %Z")

message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

project(
  ${PROJECT_NAME}
  VERSION 2.2.0
  DESCRIPTION "A C++ Template project for you!"
  HOMEPAGE_URL "http://www.kytok.org.ua/"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
