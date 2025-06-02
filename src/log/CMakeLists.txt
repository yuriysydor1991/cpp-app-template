cmake_minimum_required(VERSION 3.13)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LOG4CPP REQUIRED log4cpp)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE log4cpp
)

add_subdirectory(log4cpp5-init)
