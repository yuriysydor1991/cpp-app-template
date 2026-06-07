cmake_minimum_required(VERSION 3.13)

project(
  CppAppTemplate
  VERSION 0.11.0
  DESCRIPTION "A C++ Template project with only target library for you!"
  HOMEPAGE_URL "http://www.kytok.org.ua/"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/template-project-bootstrap.cmake)

message(STATUS "PROJECT_NAME: CppAppTemplate")

add_subdirectory(src)
add_subdirectory(doc)

include(template-project-feature-enabler-post)
